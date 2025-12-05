/**
 * @file hal.h
 * @author Sidharth Seela
 * @date 17th Nov 2025
 * @brief common library for lpc217x series
 */

#ifndef HAL_H
#define HAL_H
#include<lpc214x.h>
#include<assert.h>
#include<stdint.h>
enum e_timer_conf{
	TIMER,
	COUNTRISE,
	COUNTFALL,
	COUNTBOTH,
}
struct s_pinsel{
	uint8_t mode:2;
	uint8_t bank:2;
	uint8_t pin:4;
};

/**
 * @brief initialize PLL to by multiplying FOSC by mul
 * @param mul
 */
void sysPll(uint32_t mul)

/**
 * @brief start peripheral clock by dividing COSC by div
 * @param div
 */
void peripPll(uint32_t div);

/**
 * @brief use periph clock, then prescale down, and wait for reps
 * @param timernum 0 or 1
 * @div 1 - max
 * @reps 0 - max
 */
void delay(uint8_t timernum,uint32_t div,uint32_t  reps);

/**
 * @brief use pinsel to set mode of gpio using struct s_pinsel
 * @param pin
 */
void pinsel(struct s_pinsel pin);
#endif

