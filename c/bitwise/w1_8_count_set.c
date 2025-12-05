#include<stdio.h>
#define COUNT_SET(count,x)	{for (int i = 0; i<32; i++){\
					count += (1 && (x & (1 << i)));\
				}}
int main(){
	int z = 33;
	int count = 0;
	COUNT_SET(count,z);
	printf("count set bits %d\n",count);
}
