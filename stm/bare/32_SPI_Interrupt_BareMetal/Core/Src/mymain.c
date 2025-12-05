#include "stm32l476xx.h"
#include <stdint.h>

static volatile const uint8_t tx_buf[5] = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5};
static volatile uint32_t tx_len = 5;
static volatile uint32_t tx_idx = 0;
static volatile uint8_t tx_in_progress = 0;
static volatile uint8_t tx_done = 0;

static void delay_nops(volatile uint32_t n) { while (n--) __asm__("nop"); }

static void clocks_enable(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    (void)RCC->AHB2ENR;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    (void)RCC->AHB2ENR;
    RCC->APB1ENR1 |= RCC_APB1ENR1_SPI3EN;
    (void)RCC->APB1ENR1;
}

static void gpio_spi3_init(void)
{
    GPIOC->MODER &= ~((GPIO_MODER_MODE10) | (GPIO_MODER_MODE11) | (GPIO_MODER_MODE12));
    GPIOC->MODER |=  (GPIO_MODER_MODE10_1 | GPIO_MODER_MODE11_1 | GPIO_MODER_MODE12_1);

    GPIOC->AFR[1] &= ~((0xFU << ((10-8)*4)) | (0xFU << ((11-8)*4)) | (0xFU << ((12-8)*4)));
    GPIOC->AFR[1] |=  ((6U << ((10-8)*4)) | (6U << ((11-8)*4)) | (6U << ((12-8)*4)));

    GPIOC->OTYPER &= ~((1U<<10)|(1U<<11)|(1U<<12));
    GPIOC->OSPEEDR |=  (GPIO_OSPEEDR_OSPEED10 | GPIO_OSPEEDR_OSPEED11 | GPIO_OSPEEDR_OSPEED12);
    GPIOC->PUPDR   &= ~((GPIO_PUPDR_PUPDR10) | (GPIO_PUPDR_PUPDR11) | (GPIO_PUPDR_PUPDR12));

    GPIOA->MODER &= ~GPIO_MODER_MODE15;
    GPIOA->MODER |=  GPIO_MODER_MODE15_0;
    GPIOA->OTYPER &= ~(1U<<15);
    GPIOA->PUPDR  &= ~GPIO_PUPDR_PUPDR15;
    GPIOA->BSRR    = (1U<<15);
}

static void spi3_master_init(void)
{
    SPI3->CR1 &= ~SPI_CR1_SPE;
    uint32_t cr1 = 0;
    cr1 |= SPI_CR1_MSTR;

    cr1 |= SPI_CR1_BR_1;

    cr1 |= SPI_CR1_SSM | SPI_CR1_SSI;
    SPI3->CR1 = cr1;
    SPI3->CR1 |= SPI_CR1_SPE;
}

static inline void cs_assert(void)  { GPIOA->BRR = (1U<<15); }
static inline void cs_deassert(void){ GPIOA->BSRR = (1U<<15); }

static void nvic_spi3_enable(void)
{
    NVIC_SetPriority(SPI3_IRQn, 2);
    NVIC_EnableIRQ(SPI3_IRQn);
}

void SPI3_IRQHandler(void)
{
    if (SPI3->SR & SPI_SR_TXE) {
        if (tx_idx < tx_len) {
            *((__IO uint8_t *)&SPI3->DR) = tx_buf[tx_idx++];
        } else {
            SPI3->CR2 &= ~SPI_CR2_TXEIE;
            tx_in_progress = 0;
            tx_done = 1;
        }
    }
}

static void spi3_start_tx_interrupt(void)
{
    if (tx_in_progress) return;
    tx_idx = 0;
    tx_done = 0;
    tx_in_progress = 1;
    SPI3->CR2 |= SPI_CR2_TXEIE;
}

void mymain(void)
{
    clocks_enable();
    gpio_spi3_init();
    spi3_master_init();
    nvic_spi3_enable();
    delay_nops(10000);

    cs_assert();
    spi3_start_tx_interrupt();

    while (!tx_done) { __asm__("wfi"); }

    while (SPI3->SR & SPI_SR_BSY) { __asm__("nop"); }

    cs_deassert();

    while (1) { __asm__("wfi"); }
}
