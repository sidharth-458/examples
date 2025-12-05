#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	char arr[100];
	scanf("%99[^\\n]s",arr);
	printf("%s\n",arr);
}
