#include<stdio.h>

int getsize(int a){
	int max = 0;
	for(int i = 0; i<32;i++){
		if(a & 1)
			max = i + 1;
		a = a>>1;
	}
	return max;
}	
int main(){
	printf("size %d\n",getsize(4));
}
