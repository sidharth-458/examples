#include<stdio.h>
#define IS_PWR(x) (x & (x - 1)) == 0
int main(){
	int x = 31;
	printf("IS_PWR %d\n",IS_PWR(x));
}

