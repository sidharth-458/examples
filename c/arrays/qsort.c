#include<stdio.h>
#include<stdlib.h>

#define PRINT(x) print(x,sizeof(x)/sizeof(int))

void print(int arr[],int size){
	for(int i = 0 ; i <size; i++)
		printf("%d ",*(arr +i));
	printf("\n");
}
int compare(const void * a, const void *b){
	int *ia ,*ib;
	ia = (int *)a;
	ib = (int *)b;

	return - *ia + *ib;
}
int main(){
	int arr[] = {1,2,3,4,5};
	PRINT(arr);
	qsort(arr,5,sizeof(int),compare);
	PRINT(arr);
}
