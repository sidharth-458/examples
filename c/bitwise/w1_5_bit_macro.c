#include<stdio.h>
#define LSB_SET(x) 1 && (x & 0x1)
#define MSB_SET(x) 1 && (x & (0x1 << 31))

#define BIT_SET(x,n) x | (0x1 << n)
#define BIT_CLR(x,n) x &~(0x1 << n)
#define BIT_TOG(x,n) x ^ (0x1 << n)

int main(){
	unsigned int val = 0;
	
	printf("bit SET %d\n",BIT_SET(val,2));
	
	val = 1 << 31;
	printf("bit clear %d\n",BIT_CLR(val,31));

	val = 1 << 31;
	printf("bit toggle%d\n",BIT_TOG(val,31));
	return 0;
}
