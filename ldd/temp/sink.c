#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/poll.h>
#define atomic_t int
#define delay sleep
#define wait_queue_head_t int
#include<sys/ioctl.h>
#include"if.h"

int main(){
	int fd = open("/dev/temp0",0666);
	struct pollfd pfd[1];
	pfd[0].fd = fd;
	pfd[0].events = POLLPRI;
	while(1){
		poll(pfd,1,-1);
		printf("alert\n");
		delay(1);
	}
}
