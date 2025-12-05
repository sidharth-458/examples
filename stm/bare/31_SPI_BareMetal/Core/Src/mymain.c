#include "stm32l476xx.h"
#include <stdint.h>

#define CMD_BYTE 0x9A

static void delay_nops(volatile uint32_t n) { while (n--) __asm__("nop"); }

static void clocks_enable(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_SPI3EN;
}

static void gpio_spi3_init(void)
{
    GPIOC->MODER &= ~((GPIO_MODER_MODE10) | (GPIO_MODER_MODE11) | (GPIO_MODER_MODE12));
    GPIOC->MODER |=  (GPIO_MODER_MODE10_1 | GPIO_MODER_MODE11_1 | GPIO_MODER_MODE12_1);

    GPIOC->AFR[1] &= ~((0xF << ((10-8)*4)) | (0xF << ((11-8)*4)) | (0xF << ((12-8)*4)));
    GPIOC->AFR[1] |=  ((6 << ((10-8)*4)) | (6 << ((11-8)*4)) | (6 << ((12-8)*4)));

    GPIOC->OTYPER &= ~((1<<10)|(1<<11)|(1<<12));
    GPIOC->OSPEEDR |=  (GPIO_OSPEEDR_OSPEED10 | GPIO_OSPEEDR_OSPEED11 | GPIO_OSPEEDR_OSPEED12);
    GPIOC->PUPDR   &= ~((GPIO_PUPDR_PUPDR10) | (GPIO_PUPDR_PUPDR11) | (GPIO_PUPDR_PUPDR12));

    GPIOA->MODER &= ~GPIO_MODER_MODE15;
    GPIOA->MODER |=  GPIO_MODER_MODE15_0;
    GPIOA->OTYPER &= ~(1<<15);
    GPIOA->PUPDR  &= ~GPIO_PUPDR_PUPDR15;
    GPIOA->BSRR    = (1<<15);
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

static inline void cs_assert(void)  { GPIOA->BRR = (1<<15); }
static inline void cs_deassert(void){ GPIOA->BSRR = (1<<15); }

static void spi3_send(const uint8_t *txbuf, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
        while (!(SPI3->SR & SPI_SR_TXE)) {}
        *((__IO uint8_t *)&SPI3->DR) = txbuf[i];
        while (SPI3->SR & SPI_SR_BSY) {}
    }
}

void mymain(void)
{
    clocks_enable();
    gpio_spi3_init();
    spi3_master_init();
    delay_nops(10000);

    uint8_t tx = CMD_BYTE;

    cs_assert();
    spi3_send(&tx, 1);
    cs_deassert();

    while (1) { __asm__("wfi"); }
}
