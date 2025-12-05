#include<stdio.h>

#define SWAP(num) ((num & 0x55555555)<<1 | (num & 0xaaaaaaaa) >> 1)

int main(){
	int a = 0x12345678;
	printf("%032b\n",a);
	printf("%032b\n",SWAP(a));
	return 0;
}
