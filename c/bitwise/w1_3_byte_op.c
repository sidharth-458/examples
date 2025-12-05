#include<stdio.h>
#define LSB_SET(x) x | 0xff
#define MSB_SET(x) x | (0xff << 24)
#define MSN_SET(x) x | (0xf << 28)
#define LSN_SET(x) x | 0xf
#define N_BITS_SET(x,n)  x | ((1U << (n)) - 1U)
#define N_BITS_CLR(x,n) x & ~((1U << (n)) - 1U)
#define N_BITS_TOG(x,n) x ^ ((1u << (n)) - 1U)
int main(){
	unsigned int val = 0;
	
	val = LSB_SET(val);
	printf("LSB SET %x\n",val);
	
	val = MSB_SET(val);
	printf("MSB SET %x\n",val);
	
	val = 0;
	val = LSN_SET(val);
	printf("LSN SET %x\n",val);
	
	val = MSN_SET(val);
	printf("MSN SET %x\n",val);
	
	val = 16;
	val = N_BITS_SET(val,4);
	printf("SET N %x\n",val);
	
	val = N_BITS_CLR(val,4);
	printf("CLR N %x\n",val);

	val = N_BITS_TOG(val,4);
	printf("TOG N %x\n",val);

	return 0;
}
