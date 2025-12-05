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
int revbits(int x){
	int temp = 0;
	for(int i =0; i<32;i++){
		if( x & (1<<i) && (i%2 == 0))
			temp |= (1<< (31 - i));
	}
	return temp;
}
int main(){
	int a = revbits(1);
	printf("result %d\n",a);
}
