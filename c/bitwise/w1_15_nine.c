#include<stdio.h>
int mul9(int a){
	a = (a<<3) + a;	
	return a;
}
int main(){
	int a = 2;
	printf("%d\n",mul9(a));
}
