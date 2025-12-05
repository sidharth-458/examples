#include<stdio.h>

int highest(int number){
	int i = 0;
	for(;i<32;i++){
		if(!number){
			break;
		}
		number=number>>1;
	}
	if(0 == i)
		i = -1;

	return i;

}

int lowest(int number){
	int i = 33;
	for(;i>0;i--){
		if(!number)
			break;
		number=number<<1;
	}
	if(33 == i)
		i = -1;
	return i;
}
int main(){
	int i = 0;// 1<<31;
	printf("%d\n",highest(i));
	printf("%d\n",lowest(i));
	return 0;
}
