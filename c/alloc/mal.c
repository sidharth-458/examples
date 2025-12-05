#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define SIZE 130000
int a = 23;
int main(){
	printf("%p\n",&a);
	void * mal = malloc(SIZE);
	printf("%p\n",mal);
	void * pal = malloc(SIZE);
	printf("%p\n",pal);
	/*	char * h = "hello";
	printf("%zu\n",strlen(h));
	memcpy(mal,h,strlen(h));
	printf("%s\n",(char *)mal);
	free(mal);
	pause();
*/
}


