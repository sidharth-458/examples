#include<stdio.h>
#include<sys/signal.h>
#include<stdlib.h>
#include<unistd.h>
void (*handler)(int);

void attach(void (*h)(int)){
	handler = h;
}

void actual_handler(int a){
	printf("signum %d\n",a);
}

int main(){
	attach(actual_handler);
	signal(SIGINT,handler);
	pause();
}
