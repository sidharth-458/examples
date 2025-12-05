/*
 * usart2_dma_hello_it.c
 *
 * STM32L476 (Nucleo-L476) - minimal register-level example:
 * Send "hello\r\n" repeatedly over USART2 using DMA (interrupt-driven).
 *
 * No HAL used. Uses CMSIS device headers (stm32l4xx.h).
 *
 * Assumptions / things to adapt if needed:
 *  - USER_PCLK1_HZ must match your APB1 clock (default here is 80 MHz)
 *  - DMA_CHANNEL chosen here is 7 (DMA1_Channel7). Change if your board uses another channel.
 *
 * Build: include appropriate device headers and startup/ld scripts for your toolchain.
 */

#include "stm32l4xx.h"
#include <stdint.h>
#include <string.h>

/* ========== User configuration ========== */
#define USER_PCLK1_HZ   80000000UL   /* APB1 peripheral clock (Hz) — set to your clock */
#define BAUDRATE        115200U

/* Choose DMA channel used for USART2_TX.
   Common CubeMX examples often use DMA1_Channel7 for USART2_TX on STM32L476. */
#define DMA_CHANNEL     7U

/* Message stored into RAM (not const) to avoid flash/RAM DMA restrictions */
static uint8_t hello_ram[] = "hello\r\n";
static const uint32_t hello_len = sizeof(hello_ram) - 1U;

/* DMA status codes */
#define DMA_TC_OK        0
#define DMA_TC_ERR_TE   -2
#define DMA_TC_BUSY     127
#define DMA_TC_TIMEOUT  -1

/* volatile status set by IRQ handler */
static volatile int dma1_ch7_status = DMA_TC_BUSY;

/* Small busy-wait delay */
static void short_delay(volatile uint32_t n) {
    while (n--) __asm__("nop");
}

/* --- GPIO: PA2 -> USART2_TX (AF7) --- */
static void gpioa_pa2_usart2_tx_init(void)
{
    /* enable GPIOA clock */
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    __DSB();

    /* PA2 -> AF mode (MODER bits = 10) */
    GPIOA->MODER &= ~(0x3U << (2 * 2));
    GPIOA->MODER |=  (0x2U << (2 * 2));

    /* AF7 on PA2 (AFR[0], 4*2) */
    GPIOA->AFR[0] &= ~(0xFU << (4 * 2));
    GPIOA->AFR[0] |=  (0x7U << (4 * 2));

    /* No pull-up/pull-down (optional) */
    GPIOA->PUPDR &= ~(0x3U << (2 * 2));

    short_delay(100);
}

/* --- USART2 init: 8N1, TE enabled, DMA TX enabled --- */
static uint32_t usart_brr_from_pclk(uint32_t pclk, uint32_t baud)
{
    /* oversampling by 16: BRR = pclk / baud (rounded) */
    return (pclk + (baud / 2U)) / baud;
}

static void usart2_init(uint32_t pclk1_hz, uint32_t baud)
{
    /* enable USART2 clock on APB1 */
    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
    __DSB();

    /* disable USART before config */
    USART2->CR1 &= ~USART_CR1_UE;

    /* default control regs: 8N1, no parity */
    USART2->CR1 = 0;
    USART2->CR2 = 0;
    USART2->CR3 = 0;

    /* baudrate: simple integer BRR (oversamp = 16) */
    USART2->BRR = usart_brr_from_pclk(pclk1_hz, baud);

    /* enable transmitter */
    USART2->CR1 |= USART_CR1_TE;

    /* enable DMA transmitter */
    USART2->CR3 |= USART_CR3_DMAT;

    /* enable USART */
    USART2->CR1 |= USART_CR1_UE;

    /* small settle */
    short_delay(1000);
}

/* --- Helper to return pointer to DMA1 channel registers by channel number --- */
static volatile DMA_Channel_TypeDef *dma1_ch_ptr(uint32_t channel)
{
    switch (channel) {
#if defined(DMA1_Channel1)
    case 1: return DMA1_Channel1;
#endif
#if defined(DMA1_Channel2)
    case 2: return DMA1_Channel2;
#endif
#if defined(DMA1_Channel3)
    case 3: return DMA1_Channel3;
#endif
#if defined(DMA1_Channel4)
    case 4: return DMA1_Channel4;
#endif
#if defined(DMA1_Channel5)
    case 5: return DMA1_Channel5;
#endif
#if defined(DMA1_Channel6)
    case 6: return DMA1_Channel6;
#endif
#if defined(DMA1_Channel7)
    case 7: return DMA1_Channel7;
#endif
    default: return (volatile DMA_Channel_TypeDef *)0;
    }
}

/* --- DMA init: configure DMA1 clock and channel static bits --- */
static void dma1_channel_init_for_usart2_tx(uint32_t channel)
{
    /* Enable DMA1 clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    __DSB();

    volatile DMA_Channel_TypeDef *ch = dma1_ch_ptr(channel);
    if (!ch) return;

    /* disable channel during setup */
    ch->CCR &= ~DMA_CCR_EN;
    __DSB();

    /* clear any pending flags for this channel */
    uint32_t ifcr_mask = (0xFU << ((channel - 1U) * 4U));
    DMA1->IFCR = ifcr_mask;

    /* Configure CCR:
       - DIR = 1 (memory -> peripheral)
       - MINC = 1 (memory increment)
       - PSIZE = 00 (8-bit)
       - MSIZE = 00 (8-bit)
       - PL = 11 (very high priority)
       (Leave TCIE/TEIE disabled here; they'll be enabled when starting transfer.)
    */
    uint32_t ccr = 0;
    ccr |= DMA_CCR_DIR;      /* mem -> periph */
    ccr |= DMA_CCR_MINC;     /* memory increment */
    /* PSIZE = 00 (already 0), MSIZE = 00 (already 0) */
    ccr |= (3U << DMA_CCR_PL_Pos);  /* priority very high (3) */

    ch->CCR = ccr;

    /* peripheral address: USART2->TDR */
    ch->CPAR = (uint32_t)&(USART2->TDR);

    /* Note: CMAR and CNDTR set at transfer start */
}

/* --- NVIC enable for DMA1 channel 7 IRQ --- */
static void dma1_ch7_enable_irq(void)
{
#ifdef DMA1_Channel7_IRQn
    NVIC_ClearPendingIRQ(DMA1_Channel7_IRQn);
    NVIC_EnableIRQ(DMA1_Channel7_IRQn);
#else
    /* If your headers name IRQ differently, adapt here */
#endif
}

/* --- IRQ handler for DMA1 Channel 7 --- */
/* If you change DMA_CHANNEL ensure handler name and masks are adapted.
   For channel 7: bits in ISR are at positions 24..27: GIF7=24,TCIF7=25,HTIF7=26,TEIF7=27 */
void DMA1_Channel7_IRQHandler(void)
{
    uint32_t isr = DMA1->ISR;
    const uint32_t tcif7 = (1U << (4U*(7U-1U) + 1U));  /* bit 25 */
    const uint32_t teif7 = (1U << (4U*(7U-1U) + 3U));  /* bit 27 */

    if (isr & tcif7) {
        /* clear TC */
        DMA1->IFCR = tcif7;
        dma1_ch7_status = DMA_TC_OK;
    }
    if (isr & teif7) {
        /* clear TE */
        DMA1->IFCR = teif7;
        dma1_ch7_status = DMA_TC_ERR_TE;
    }
}

/* --- Start DMA transfer on DMA1 channel 7, using IRQ completion --- */
static int dma1_ch7_start_tx_it(const uint8_t *buf, uint32_t len, uint32_t timeout_cycles)
{
#if !defined(DMA1_Channel7)
    (void)buf; (void)len; (void)timeout_cycles;
    return DMA_TC_TIMEOUT;
#else
    volatile DMA_Channel_TypeDef *ch = DMA1_Channel7;

    /* disable channel before configuring */
    ch->CCR &= ~DMA_CCR_EN;
    __DSB();

    /* set memory address and number of data */
    ch->CMAR  = (uint32_t)buf;
    ch->CNDTR = len;

    /* clear flags for this channel (GIF/TC/HT/TE) */
    DMA1->IFCR = (0xFU << ((7U - 1U) * 4U));

    /* enable TCIE and TEIE in CCR (interrupts) */
    ch->CCR |= (DMA_CCR_TCIE | DMA_CCR_TEIE);

    /* ensure NVIC enabled */
    dma1_ch7_enable_irq();

    /* mark busy */
    dma1_ch7_status = DMA_TC_BUSY;

    /* enable channel */
    ch->CCR |= DMA_CCR_EN;

    /* wait for completion or error or timeout */
    uint32_t cnt = timeout_cycles;
    while (dma1_ch7_status == DMA_TC_BUSY) {
        if (cnt) {
            if (--cnt == 0U) {
                /* timeout: disable channel and return */
                ch->CCR &= ~DMA_CCR_EN;
                return DMA_TC_TIMEOUT;
            }
        }
    }

    /* disable channel after completion */
    ch->CCR &= ~DMA_CCR_EN;

    return dma1_ch7_status;
#endif
}

/* --- small helper: wait until USART TXE=1 (data register empty) --- */
static void wait_usart_txe(void)
{
    while (!(USART2->ISR & USART_ISR_TXE)) { }
}

/* --- Main --- */
void mymain(void)
{
    /* (Optional) copy message to RAM - it's already in RAM as hello_ram */
    /* If you had const in flash you would copy to an SRAM buffer here */

    /* 1) GPIO init for PA2 = USART2_TX */
    gpioa_pa2_usart2_tx_init();

    /* 2) USART init */
    usart2_init(USER_PCLK1_HZ, BAUDRATE);

    /* 3) DMA init for channel 7 (clear, set CPAR, CCR static bits) */
    dma1_channel_init_for_usart2_tx(DMA_CHANNEL);

    /* 4) main loop: send hello via DMA with IRQ completion */
    while (1) {
        /* Ensure USART ready to accept (TXE = 1) */
        wait_usart_txe();

        /* Kick DMA transfer (timeout ~ 1 second worth of cycles; adjust as needed) */
        int rc = dma1_ch7_start_tx_it(hello_ram, hello_len, 2000000U);

        if (rc == DMA_TC_OK) {
            /* success — optionally wait short time before next message */
            for (volatile uint32_t i = 0; i < 200000U; ++i) __asm__("nop");
        } else if (rc == DMA_TC_ERR_TE) {
            /* DMA transfer error: hang here for debug (or handle) */
            while (1) {
                __asm__("nop");
            }
        } else {
            /* timeout or other error — hang for debug */
            while (1) {
                __asm__("nop");
            }
        }
    }

}
