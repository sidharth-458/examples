#ifndef STM32F476XX_H
#define STM32F476XX_H
#include<stdint.h>

#define FLASH_ADDR	0x08000000U
#define SRAM1_ADDR	0X20000000U
#define SRAM2_ADDR	0x10000000U
#define ROM_ADDR	0x1fff0000U
#define OTP_ADDR	0x1fff7000U

#define AHB1_ADDR	0x40020000U
#define AHB2_ADDR	0x48000000U
#define APB1_ADDR	0x40000000U
#define APB2_ADDR	0x40010000U

#define RCC_ADDR	0x40021000U

#define GPIOA_ADDR	(AHB2_ADDR + 0)
#define _vo volatile uint32_t

struct gpio{
	_vo MODER;
	_vo OTYPER;
	_vo OSPEEDR;
	_vo PUPDR;
	_vo IDR;
	_vo ODR;
	_vo BSRR;
	_vo LCKR;
	_vo AFRL;
	_vo AFRH;
	_vo BRR;
};

#define GPIOA ((struct gpio*)GPIOA_ADDR)

struct rcc{
	_vo CR;		//0
	_vo ICSCR;	//4
	_vo CFGR;	//8
	_vo PLL_CFGR;	//c
	_vo PLLSAICFGR[2];//14
	_vo CIER;		//18
	_vo CIFR;		//1c
	_vo CICR;		//20
	_vo :32;			//24
	_vo AHBRSTR[3];	//28
	_vo :32;			//34
	_vo APB1RSTR[2];//38
	_vo APB2RSTR1;	//40
	_vo :32;			//44
	_vo AHBENR[3];	//48
	_vo;			//54
	_vo APB1ENR[2];
	_vo APB2ENR;
	_vo AHBSMENR[3];
	_vo APB1SMENR[2];
	_vo APB2SMENR;
	_vo CCIPR;
	_vo BDCR;
	_vo CSR;
	_vo CRRCR;
	_vo CCIPR2;
	_vo DLYCFGR;
};

#define RCC ((struct rcc *)RCC_ADDR)

/*ENABLE DISABLE CLOCK*/
#define GPIOA_CLK_EN() (RCC->AHBENR[1] |=  (1<<0))
#define GPIOA_CLK_DI() (RCC->AHBENR[1] &= ~(1<<0))
#endif
