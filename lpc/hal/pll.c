#include"hal.h"
/**
 * @brief initialize PLL to by multiplying FOSC by M
 */
void sysPll(uint32_t mul){
	if(!mul)
		assert(0);
		
	/*enable*/
	PLL0CON = 0x01;
	
	/*MSEL 5(M) * 12(fosc) = 60(cco) Note: M - 1,for non-zero*/
	PLL0CFG = mul - 1;
	
	/*PSEL */
	PLL0CFG |= 0x20;
	
	/*PASSWORD*/
	PLL0FEED = 0xaa;
	PLLOFEED = 0x55;

	/*Wait to stabilize to 1*/
	while(!(PLL0STAT & 0x400));

	/*connect*/
	PLL0CON |= 0x02;

	/*PASSWORD*/
	PLL0FEED = 0xaa;
	PLL0FEED = 0x55;

}

/**
 * @brief start peripheral clock with x divider from COSC
 */
void peripPll(uint32_t div){
	if(!div)
		assert(0);
	/*peripheral divider reg*/
	VPBDIV = div - 1;
}
