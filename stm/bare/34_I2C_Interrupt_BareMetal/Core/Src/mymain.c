#include "stm32l476xx.h"
#include <stdint.h>

static const uint8_t tx_buf[5] = {0xA1, 0xB2, 0xC3, 0xD4, 0xE5};
volatile uint32_t tx_len = 5;
volatile uint32_t tx_idx = 0;
volatile int result = -1; /* 0=ACK, 1=NACK, 2=TIMEOUT */
volatile uint8_t done = 0;

static void short_delay(volatile uint32_t n) { while (n--) __asm__("nop"); }

static void i2c1_enable_clocks_gpio(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    (void)RCC->AHB2ENR;
    RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN;
    (void)RCC->APB1ENR1;
}

static void i2c1_gpio_init(void)
{
    GPIOB->MODER &= ~(GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
    GPIOB->MODER |=  (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
    GPIOB->AFR[0] &= ~((0xFU << (6*4)) | (0xFU << (7*4)));
    GPIOB->AFR[0] |=  ((4U << (6*4)) | (4U << (7*4)));
    GPIOB->OTYPER |= ((1U<<6) | (1U<<7));
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPDR6 | GPIO_PUPDR_PUPDR7);
    GPIOB->PUPDR |=  ((1U<<12) | (1U<<14));
    GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEED6 | GPIO_OSPEEDR_OSPEED7);
}

static void i2c1_init_timing(void)
{
    I2C1->CR1 &= ~I2C_CR1_PE;
    I2C1->TIMINGR = (3U << 28) | (1U << 20) | (3U << 16) | (0x13U << 8) | (0x0FU << 0);
    I2C1->CR1 |= I2C_CR1_PE;
    short_delay(1000);
}

static void nvic_i2c_enable(void)
{
    NVIC_SetPriority(I2C1_EV_IRQn, 2);
    NVIC_EnableIRQ(I2C1_EV_IRQn);
    NVIC_SetPriority(I2C1_ER_IRQn, 2);
    NVIC_EnableIRQ(I2C1_ER_IRQn);
}

static void i2c1_start_master_tx(uint8_t addr7, const uint8_t *buf, uint32_t len)
{
    tx_idx = 0;
    tx_len = len;
    done = 0;
    result = -1;

    I2C1->ICR = I2C_ICR_STOPCF | I2C_ICR_NACKCF;

    uint32_t sadd = ((uint32_t)addr7 << 1);
    uint32_t cr2 = (sadd << I2C_CR2_SADD_Pos);


    cr2 |= (len << I2C_CR2_NBYTES_Pos);
    cr2 |= I2C_CR2_AUTOEND;
    cr2 |= I2C_CR2_START;
    I2C1->CR2 = cr2;

    I2C1->CR1 |= (I2C_CR1_TXIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE);
}
int timeout = 0;
void I2C1_EV_IRQHandler(void)
{
    uint32_t isr = I2C1->ISR;

    if (isr & I2C_ISR_TXIS) {
        if (tx_idx < tx_len) {
            I2C1->TXDR = tx_buf[tx_idx++];
        } else {
            I2C1->CR1 &= ~I2C_CR1_TXIE;
        }
    }

    if (isr & I2C_ISR_NACKF) {
        I2C1->ICR = I2C_ICR_NACKCF;
        result = 1;
        done = 1;
        timeout = 1;
        I2C1->CR1 &= ~(I2C_CR1_TXIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE);
    }

    if (isr & I2C_ISR_STOPF) {
        I2C1->ICR = I2C_ICR_STOPCF;
        if (result == -1) result = 0;
        done = 1;
        I2C1->CR1 &= ~(I2C_CR1_TXIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE);
    }
}

void I2C1_ER_IRQHandler(void)
{
    uint32_t isr = I2C1->ISR;
    if (isr & (I2C_ISR_ARLO | I2C_ISR_BERR | I2C_ISR_OVR)) {
        I2C1->ICR = I2C_ICR_ARLOCF | I2C_ICR_BERRCF | I2C_ICR_OVRCF;
        result = 1;
        done = 1;
        I2C1->CR1 &= ~(I2C_CR1_TXIE | I2C_CR1_NACKIE | I2C_CR1_STOPIE);
    }
}

void mymain(void)
{
    i2c1_enable_clocks_gpio();
    i2c1_gpio_init();
    i2c1_init_timing();
    nvic_i2c_enable();

    i2c1_start_master_tx(0x21U, tx_buf, 5U);

    volatile uint32_t wait = 3000000U;
    while (wait--);
    timeout = timeout;//if 1 timeout
    while (1) { __asm__("wfi"); }
}
