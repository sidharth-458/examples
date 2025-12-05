#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define MODE(x) mode(x,sizeof(x)/sizeof(int))

int compare(const void *a,const void *b){
	return *(int *)a - * (int*)b;
}

void mode(int arr[],int size){
	int max = 0;
	int curr = 0;
	int localref = arr[0];
	qsort(arr,size,sizeof(int),compare);
	for(int i = 0; i<size;i++){
		if(arr[i] != localref){
			localref = arr[i];
			curr = 0;
		}
		curr++;

		if(curr > max)
			max = curr;
	};
	printf("%d\n",max);
	
}
int main(){
	int arr[] = {-INT_MAX, 1, -2, 3,5,-100,45,45,32,45,23,45};
	MODE(arr);
}
