#include<stdio.h>
int swap(int a){
	int mask = 0x55555555;
	a = (a & mask)<<1 | (a & (mask<<1))>>1;
	return a;
}
int main(){
	int a = 0x34567;
	printf("%032b %032b\n",a,swap(a));
}
