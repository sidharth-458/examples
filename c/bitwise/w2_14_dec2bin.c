#include<stdio.h>

void dec2bin(int num){
	for(int i = 31;i>=0;i--){
		printf("%d", 1 && (num & (1<<i)));
	}
	printf("\n");
}
int main(){
	dec2bin(10);
};
