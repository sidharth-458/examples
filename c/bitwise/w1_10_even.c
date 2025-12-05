#include<stdio.h>
#define IS_EVEN(x) (x & 1) == 0
int main(){
	int x = 32;
	printf("IS_EVEN %d\n",IS_EVEN(x));
}

