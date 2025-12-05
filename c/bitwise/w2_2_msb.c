#include<stdio.h>
#define LSB_SET(x) 1 && (x & 0x1)
#define MSB_SET(x) 1 && (x & (0x1 << 31))
#define BIT_SET(x,n) 1 && (x & (0x1 << n))
int main(){
	unsigned int val = 33;
	
	printf("LSB SET %d\n",LSB_SET(val));
	
	printf("MSB SET %d\n",MSB_SET(val));

	printf("BIT@4 set %d\n",BIT_SET(val,4));
	return 0;
}
