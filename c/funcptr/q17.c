#include<stdio.h>
#include<stdlib.h>
typedef int (*fp)(int,int);

int add(int,int){
}
int sub(int,int){
}

struct calc{
	int oper1;
	int oper2;
	fp functions[2];
};
int calcinit(struct calc * c){
	c->functions[0] = add;
	c->functions[1] = sub;	
}


int main(){
	struct  calc * calc = malloc(sizeof(struct calc));
	calcinit(calc);
}
