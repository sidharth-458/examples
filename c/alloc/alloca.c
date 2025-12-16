#include<stdio.h>

#include<alloca.h>
#include<stdint.h>
#include<limits.h>
void allo(){
	int * arr = alloca(sizeof(int) * 10000000);
	for(int i =0;i<SIZE_MAX;i++){
		arr[i] = i;
		printf("%d\n",arr[i]);
	}
	printf("done\n");
}
int main(){
	allo();
	return 0;
}
