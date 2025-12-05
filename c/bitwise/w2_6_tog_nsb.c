#include<stdio.h>
#define LSB_SET(x) x | 1
#define LSB_CLR(x) x & 0
#define LSB_TOG(x) x ^ 1
#define MSB_SET(x) x | (1<<31)
#define MSB_CLR(x) x & ~(1<<31)
#define MSB_TOG(x) x ^ (1<<31)
int main(){
	unsigned int val = 0;
	
	val = LSB_SET(val);
	printf("LSB SET %x\n",val);
	
	val = LSB_CLR(val);
	printf("LSB CLR %x\n",val);
	
	val = LSB_TOG(val);
	printf("LSB TOG %x\n",val);

	val = MSB_SET(val);
	printf("MSB SET %x\n",val);
	
	val = MSB_CLR(val);
	printf("MSB CLR %x\n",val);
	
	val = MSB_TOG(val);
	printf("MSB TOG %x\n",val);
	
	return 0;
}
