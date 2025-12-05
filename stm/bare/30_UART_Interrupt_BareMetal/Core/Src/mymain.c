

#include "stm32l476xx.h"
#include <stdint.h>
#include"main.h"
#include <string.h>

static const uint8_t tx_msg[] = "hello\r\n";
static volatile uint32_t tx_len = 0;
static volatile uint32_t tx_idx = 0;

#define BAUDRATE 115200U

static void short_delay(volatile uint32_t n) { while (n--) __asm__("nop"); }

static void periph_clocks_enable(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    (void)RCC->AHB2ENR;

    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
    (void)RCC->APB1ENR1;
}

static void gpioa_pa2_usart2_tx_init(void)
{
    GPIOA->MODER &= ~GPIO_MODER_MODE2;            /* clear */
    GPIOA->MODER |=  GPIO_MODER_MODE2_1;          /* AF mode (10) */

    GPIOA->OTYPER &= ~GPIO_OTYPER_OT_2;

    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED2;
    GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED2_0 | GPIO_OSPEEDR_OSPEED2_1);

    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR2;

    uint32_t afr_shift = (2U & 0x7U) * 4U;
    GPIOA->AFR[0] &= ~(0xFU << afr_shift);
    GPIOA->AFR[0] |= (7U << afr_shift); /* AF7 = USARTx */
}

static uint32_t compute_usart_brr(uint32_t baud)
{
    uint32_t hclk = SystemCoreClock;

#ifdef RCC_CFGR_PPRE1_Pos
    uint32_t ppre1 = (RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos;
#else
    uint32_t ppre1 = (RCC->CFGR & 0x00000700U) >> 8U;
#endif

    uint32_t apb1_div;
    if (ppre1 < 4U) {
        apb1_div = 1U;
    } else {
        apb1_div = 1U << (ppre1 - 3U);
    }

    uint32_t pclk1 = hclk / apb1_div;

    uint64_t tmp = (uint64_t)pclk1 * 16ULL;
    uint32_t brr = (uint32_t)((tmp + (baud / 2U)) / baud);

    return brr;
}

static void usart2_tx_interrupt_init(void)
{
    USART2->CR1 &= ~USART_CR1_UE;

    USART2->CR1 &= ~(USART_CR1_M | USART_CR1_PCE);

    USART2->BRR = compute_usart_brr(BAUDRATE);

    USART2->CR1 |= USART_CR1_TE;

    USART2->CR1 |= USART_CR1_TXEIE;

    USART2->CR1 |= USART_CR1_UE;

    short_delay(1000);
}

static void nvic_usart2_enable(void)
{
    NVIC_SetPriority(USART2_IRQn, 2);
    NVIC_EnableIRQ(USART2_IRQn);
}

static void usart2_send_it(const uint8_t *buf, uint32_t len)
{
    (void)buf;
    tx_len = len;
    tx_idx = 0;

    USART2->CR1 |= USART_CR1_TXEIE;
}

void USART2_IRQHandler(void)
{
    uint32_t sr = USART2->ISR ;
    if (USART2->ISR & USART_ISR_TXE) {
        if (tx_idx < tx_len) {
            USART2->TDR = tx_msg[tx_idx++]; /* writing TDR clears TXE */
        } else {
            USART2->CR1 &= ~USART_CR1_TXEIE;

        }
    }
}

void mymain(void)
{
	SystemCoreClockUpdate();
    periph_clocks_enable();
    gpioa_pa2_usart2_tx_init();
    usart2_tx_interrupt_init();
    nvic_usart2_enable();

    usart2_send_it(tx_msg, (uint32_t)strlen((const char *)tx_msg));

    while (1) {
        __asm__("wfi"); /* wait for interrupt - low power until next IRQ */
    }

}
