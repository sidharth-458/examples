#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#define atomic_t int
#define delay sleep
#include<sys/ioctl.h>
#include"if.h"
void print(int fd){
	struct ld_state state = {0};
	ioctl(fd,LD_GET_STATE,(long) (void *)&state);
	printf("%d %d %d %d\n",state.on, state.brt,state.tmp,state.usrs);
}

int main(){
	int fd = open("/dev/lightdev0",0666);
	int brt = 0;
	int tmp = 0;
	while(1){
		ioctl(fd,LD_SET_ON,0);
		delay(2);
		ioctl(fd,LD_SET_BRT,brt++%100);
		delay(2);
		ioctl(fd,LD_SET_TMP,tmp++%4500 +2000);
		delay(2);
		ioctl(fd,LD_SET_OFF,0);
		print(fd);
		delay(2);
	}
}
