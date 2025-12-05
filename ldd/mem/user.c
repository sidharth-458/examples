#include<sys/ioctl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include"if.h"
#define SIZE 4096
#define SECTOR 512
void readbuff(int fd){
	char arr[SIZE]  = {0};
	lseek(fd,0,SEEK_SET);
	int ret = read(fd,arr,SIZE);
	if(ret < 0){
		perror("read failed");
		return;
	}
	for(int i = 0 ; i< ret;i++){
		if(arr[i] != 0){
			printf("%c",arr[i]);
		}
		else{
			printf(".");
		}
	}
	printf("\n");
}


int main(){
	int fd = open("/dev/memory0",0666);
	if(fd < 0){
		perror("file error");
		return -1;
	}
	printf("openingn\n");

//	printf("locked region 1\n");
	ioctl(fd,VBLOCK_LOCK_REGION,2);
	
	printf("trying write to region 2, with key\n");
	struct w_hd * hd;
	char buff[1000];
	hd = (struct w_hd *)buff;
	hd->key = 123;
	hd->offset = 1023;
	strcpy(buff + sizeof(struct w_hd) , "hello");

	write(fd,buff,21);
	readbuff(fd);
/*
	printf("read all\n");
	readbuff(fd);
	
	hd->key = 123;
	printf("trying write to region 1, with key\n");
	write(fd,buff,21);

	printf("read all\n");
	readbuff(fd);

	printf("erase region 1\n");
	ioctl(fd,VBLOCK_ERASE_REGION,1);

	printf("read region 1 via ioctl \n");
	struct region reg= {
		.num = 1,
	};
	ioctl(fd,VBLOCK_READ_REGION,(unsigned long) &reg);
	for(int i = 0; i<512;i++){
		printf("%c",reg.data[i]);
	}
	printf("\n");

	printf("get info on all regions\n");
	char reglock = 0;
	ioctl(fd,VBLOCK_GET_INFO,(unsigned long)&reglock);
	printf("locked itmap %08b\n",reglock);
*/
	printf("unlocking region 2\n");
	ioctl(fd,VBLOCK_UNLOCK_REGION,2);
	printf("closing\n");
	close(fd);
	return 0;
}
