#include<stdio.h>

int setbits(int x, int p, int n, int y){
	int ret; 
	ret = x;
	for(int i = p; i > p- n ; i--){
		if( y & (1<<i))
			ret = ret | (1<<i);
		else
			ret = ret & ~(1<<i);
	}
	return ret;
}
int main(){
	int a =32, b =56;

	a = setbits(a,6,3,b);
	printf("result %d\n",a);
}
