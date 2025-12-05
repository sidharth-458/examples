#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
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
		if(c == ' ' || c =='\n' || c =='\t'){
			linelen+=2;
			arrp[lines -1] = reallocarray(arrp[lines -1],linelen,sizeof(char));
			arrp[lines -1][linelen - 1] = 0;
			arrp[lines -1][linelen - 2] = c;
			if(linelen == 6){
				if(strncmp("word",arrp[lines -1],4) == 0){
					free(arrp[lines - 1]);
					asprintf(&arrp[lines - 1], "%s%c","letter",c);
				}
			}
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
	for(int i = 0; i< lines;i++){
		if(arrp[i])
			printf("%s",arrp[i]);
	}
	printf("\n");
	close(fd);
//	remove("lines.txt");
}
