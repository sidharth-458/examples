#include<stdio.h>
#include<stdlib.h>

int main(){
	char * a = malloc(0);
	printf("%ld\n",(void *) a);
	a = malloc(0);
	printf("%ld\n",(void *) a);
}

	
