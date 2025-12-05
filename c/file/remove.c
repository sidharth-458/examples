#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
	char ** arrp = NULL;
	int fd = open("lines.txt",O_RDONLY);
	off_t last = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);
	int lines = 1;
	arrp = reallocarray(arrp,lines,sizeof(char *));
	if(!arrp)
		exit(-1);
		
	int linelen = 0;
	for(int i = 0 ; i< last;i++){
		char c;
		read(fd,&c,sizeof(char));
		if(c == '\n'){
			linelen++;
			arrp[lines -1] = reallocarray(arrp[lines -1],linelen,sizeof(char));
			arrp[lines -1][linelen - 1] = 0;
			lines++;
			arrp = reallocarray(arrp,lines,sizeof(char *));
			if(!arrp)
				exit(-1);
			arrp[lines - 1] = NULL;
			linelen = 0;
		}
		else{
			linelen++;
			arrp[lines -1] = reallocarray(arrp[lines -1],linelen,sizeof(char));
			arrp[lines -1][linelen - 1] = c;
		}
	}
	printf("lines %d\n",lines - 1);
	printf("which line to delete?\n");
	int del;
	scanf("%d",&del);
	/*
	for(int i = 0; i< lines;i++){
		if(arrp[i] && i!= del)
			printf("%s\n",arrp[i]);
	}*/
	close(fd);
	fd = open("lines.txt",O_WRONLY | O_TRUNC);
	if(fd < 0){
		perror("open");
		exit(-1);
	}
	for(int i =0; i<lines;i++){
		if(arrp[i] && i!=del){
			char * ptr = NULL;
			size_t wr = 0;
			wr =asprintf(&ptr,"%s\n",arrp[i]);
			printf("%s",ptr);
			if(write(fd,ptr,wr)<=0)
				perror("write");
			free(ptr);
		}
	}
	close(fd);
//	remove("lines.txt");
}
