#include<stdlib.h>
#include<sys/signal.h>
#include<stdio.h>
#include<execinfo.h>
#define FAULT_PTR ((void *)150000)

void print_call_stack() {
    void *array[10]; // Array to store addresses
    size_t size;     // Number of frames

    // Get the backtrace
    size = backtrace(array, 10);

    // Print the backtrace symbols
    fprintf(stderr, "Call stack:\n");
    backtrace_symbols_fd(array, size, 2);
}


void segsig(int sig){
	if(sig == SIGSEGV){
		printf("seg_handler\n");
//		print_call_stack();
//		exit(-1);
	}
}
int main(){
	signal(SIGSEGV,segsig);
	void * a = malloc(1);//allocate 135KB
//	char * flt =(char*) FAULT_PTR;
//	*flt = 'c';
	printf("should not print due to seg fault\n");
}
