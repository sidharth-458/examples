#include<stdio.h>

void counts(int num){
	int ones = 0;
	for(int i =0;i<32;i++){
		if(num & (1<<i))
			ones++;
	}
	printf("ones %d, zeros %d\n",ones,32-ones);
}

int main(){
	counts(12);
	return 0;
}
