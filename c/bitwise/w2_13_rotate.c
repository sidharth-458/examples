#include<stdio.h>

int rotate(int num, int by){
	return num << by;
}

int main(){
	printf("%d\n",rotate(2));
	return 0;
}
