#include<stdio.h>
#define COUNT_SET(count,ptr)	{for (int i = 0; i<32; i++){\
					count += (1 && (*ptr & (1 << i)));\
				}}
int main(){
	float z = 33;
	int * a = (int *)&z;
	int count = 0;
	COUNT_SET(count,a);
	printf("count set bits %d\n",count);
}
