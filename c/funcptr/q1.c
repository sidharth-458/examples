#include<stdio.h>
int add(int a, int b){
	return a +b;
}
int div(int a, int b){
	return a/b;
}

int main(){
	int (*fp)(int,int) = add;
	printf("%d\n",fp(1,2));
	fp = div;
	printf("%d\n",fp(1,2));
}
