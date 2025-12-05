
#include "stm32l4xx.h"   /* device header providing register map */
#include <stdint.h>
#define PCLK1_HZ    4000000UL   /* typical default MSI-based PCLK1 on reset */
#define BAUD_RATE   9600UL

static const char msg[] = "Hello\r\n";

#define DELAY_COUNT 1000000UL

static void delay_busy(volatile uint32_t count)
{
    while (count--) {
        __asm__("nop");
    }
}

static void usart2_putc(char c)
{
    while ((USART2->ISR & USART_ISR_TXE) == 0) {

    }
    USART2->TDR = (uint32_t)(c & 0xFF);
}


static void usart2_tx_str(const char *s)
{
    while (*s) {
        usart2_putc(*s++);
    }
}



static void uart2_init(void)
{
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;     /* enable GPIOA clock */
    (void)RCC->AHB2ENR;

    RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;  /* enable USART2 clock */
    (void)RCC->APB1ENR1;

    GPIOA->MODER &= ~(3U << (2U * 2U));      /* clear mode bits for PA2 */
    GPIOA->MODER |=  (2U << (2U * 2U));      /* set AF mode */

    GPIOA->AFR[0] &= ~(0xFU << (2U * 4U));
    GPIOA->AFR[0] |=  (7U << (2U * 4U));     /* AF7 */

    GPIOA->PUPDR &= ~(3U << (2U * 2U));

    uint32_t brr = (PCLK1_HZ + (BAUD_RATE / 2U)) / BAUD_RATE; /* integer round */
    USART2->BRR = brr;

    USART2->CR1 &= ~((uint32_t)0xFFFFFFFFU);
    USART2->CR1 |= USART_CR1_TE;   /* enable transmitter */
    USART2->CR1 |= USART_CR1_UE;   /* enable USART */

    for (volatile uint32_t i = 0; i < 1000; ++i) { __asm__("nop"); }
}


void mymain(void)
{
    uart2_init();

    while (1) {
        usart2_tx_str(msg);

        delay_busy(DELAY_COUNT);
    }

}
