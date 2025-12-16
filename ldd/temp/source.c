#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#define atomic_t int
#define delay sleep
#define wait_queue_head_t int
#include<sys/ioctl.h>
#include"if.h"

int main(){
	int fd = open("/dev/temp0",0666);
	ioctl(fd,LD_SET_TMP,0);
	close(fd);
	
}
