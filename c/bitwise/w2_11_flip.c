#include<stdio.h>

int flipbits(int x, int y){
	int ret; 
	ret = 0;
	for(int i = 0; i<32 ; i++){
		if( (y & (1<<i)) != (x & (1<<i)))
			ret++;
	}
	return ret;
}
int main(){
	int a =32, b =31,count;
	count = flipbits(a,b);
	printf("result %d\n",count);
}
