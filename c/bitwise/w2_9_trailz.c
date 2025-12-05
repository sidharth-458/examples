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
int trailz(int number){
	int ret = lowest(number);
	if(ret == -1)
		return -1;
	else
		return ret -1;
}

int leadz(int number){
	int ret = highest(number);
	if(ret == -1)
		return -1;
	else
		return 32 - ret;
}

int main(){
	int i = 1<<31;
	printf("%d\n",highest(i));
	printf("%d\n",lowest(i));
	printf("%d\n",leadz(i));
	printf("%d\n",trailz(i));
	return 0;
}
