#include<stdio.h>
#include<stdlib.h>
#include<error.h>
#include<errno.h>
int main(){
#ifdef DEBUG
#include<malloc.h>
	if( mallopt(M_CHECK_ACTION,1))
		error(errno,errno,"mallopt");
#endif
	char * arr = malloc(1);
	arr[1] = 2;
	free(arr);
	free(arr);
}
