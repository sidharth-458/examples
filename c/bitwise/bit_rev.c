#include<stdio.h>

int shift(int * n){
	int ret  = *n & 0x1;
	*n= *n>>1;
	return ret;
}

int flip(int n){
	int a;
	for(int i =0; i<sizeof(int) * 8 -1 ; i++){
		a = a | shift(&n);
		a = a<<1;
	}
	return a;
}

int main(){
	int a = 0x1234abcd;
	printf("%032b\n",a);
	printf("%032b\n",flip(a));
}
