#include <stdint.h>
#include<stm32l4xx_hal.h>

#define LED_PINNUM 5
#define BTN_PINNUM 13

void mymain(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_APB2ENR_SYSCFGEN | RCC_AHB2ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    GPIOA->MODER &= ~(1U << (LED_PINNUM * 2 + 1));
    GPIOC->MODER &= ~(3U << (BTN_PINNUM * 2));
    GPIOC->PUPDR &= ~(1U << (BTN_PINNUM * 2 + 1));
    SYSCFG->EXTICR[3] |=  (2UL << 4);      // set port C (value 2) into EXTI13 field

    EXTI->RTSR1 &= ~(1UL << BTN_PINNUM);   // disable rising
    EXTI->FTSR1 |=  (1UL << BTN_PINNUM);   // enable falling

    EXTI->PR1 = (1UL << BTN_PINNUM);       // write-1 to clear pending

    EXTI->IMR1 |= (1UL << BTN_PINNUM);

    NVIC->ISER[(((uint32_t)EXTI15_10_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)EXTI15_10_IRQn) & 0x1FUL));

    while (1) {
        __asm__("wfi"); // wait for interrupt (optional)
    }
}

void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR1 & (1UL << BTN_PINNUM))
    {
        EXTI->PR1 = (1UL << BTN_PINNUM);
        for (volatile uint32_t d=0; d<30000; ++d) __asm__("nop");
        if ((GPIOC->IDR & (1UL << BTN_PINNUM)) == 0) {
            GPIOA->ODR ^= (1UL << LED_PINNUM);
        }

    }
}

