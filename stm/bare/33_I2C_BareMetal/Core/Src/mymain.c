#include "stm32l476xx.h"
#include <stdint.h>

static void short_delay(volatile uint32_t n) { while (n--) __asm__("nop"); }

static void i2c1_enable_clocks_gpio(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
}

static void i2c1_gpio_init(void)
{
    GPIOB->MODER &= ~(GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
    GPIOB->MODER |=  (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);

    GPIOB->AFR[0] &= ~((0xF << (6*4)) | (0xF << (7*4)));
    GPIOB->AFR[0] |=  ((4 << (6*4)) | (4 << (7*4)));

    GPIOB->OTYPER |= ((1<<6) | (1<<7));
    GPIOB->PUPDR  &= ~(GPIO_PUPDR_PUPDR6 | GPIO_PUPDR_PUPDR7);
    GPIOB->PUPDR  |=  ((1<<12) | (1<<14));
    GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEED6 | GPIO_OSPEEDR_OSPEED7);
}

static void i2c1_init_timing(void)
{
    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->TIMINGR = (3U << 28) | (1U << 20) | (3U << 16) | (0x13U << 8) | (0x0FU << 0);
    I2C1->CR1 |= I2C_CR1_PE;
    short_delay(1000);
}

static int i2c1_ping_address(uint8_t addr7, uint32_t timeout_loops)
{
    uint32_t t = timeout_loops;

    I2C1->ICR = I2C_ICR_STOPCF | I2C_ICR_NACKCF;

    uint32_t sadd = ((uint32_t)addr7 << 1);
    uint32_t cr2 = 0;
    cr2 |= (sadd << I2C_CR2_SADD_Pos);


    cr2 |= (1U << I2C_CR2_NBYTES_Pos);
    cr2 |= I2C_CR2_START;
    cr2 |= I2C_CR2_AUTOEND;

    I2C1->CR2 = cr2;

    while (!(I2C1->ISR & I2C_ISR_TXIS)) {
        if (I2C1->ISR & I2C_ISR_NACKF) {
            I2C1->ICR = I2C_ICR_NACKCF;
            return 1;
        }
        if (!t--) return 2;
    }

    I2C1->TXDR = 0x00;

    t = timeout_loops;

    while (1) {
        if (I2C1->ISR & I2C_ISR_STOPF) {
            I2C1->ICR = I2C_ICR_STOPCF;
            return 0;
        }
        if (I2C1->ISR & I2C_ISR_NACKF) {
            I2C1->ICR = I2C_ICR_NACKCF;
            return 1;
        }
        if (!t--) return 2;
    }
}

void mymain(void)
{
    i2c1_enable_clocks_gpio();
    i2c1_gpio_init();
    i2c1_init_timing();

    volatile int result = i2c1_ping_address(0x21, 3000000U);
    result = result;//1 nack,0 ack
    while (1) { __asm__("wfi"); }
}
