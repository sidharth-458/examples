#include<stdlib.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include"if.h"
int main(){
	int fd = open("/dev/time0",0666);

	char buff[30]  = {0};

	//read time from device file
	read(fd,buff,30);
	printf("%s\n",buff);

	//write time to device file
	int len;
	memset(buff,0,30);
	len  = snprintf(buff,30,"%d",1000);
	write(fd,buff,len);

	//read again time from device file
	read(fd,buff,30);
	printf("%s\n",buff);

	//lock file
	ioctl(fd, LOCK_CMD,0);

	//read time from device file
	read(fd,buff,30);
	printf("%s\n",buff);
	sleep(2);
	//read again time from device file after 2 seconds, will be same time
	read(fd,buff,30);
	printf("%s\n",buff);

	//unlock
	ioctl(fd,UNLOCK_CMD,0);
	
	close(fd);
	return 0;
}



	
