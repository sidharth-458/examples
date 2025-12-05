#include<stdio.h>
typedef int (*fp)(int);

int func(int a ){
	printf("hello %d\n",a);
}
fp choose(){
	return func;
}


int main(){
	int (*fp)(int) = choose();
	fp(12);
}
