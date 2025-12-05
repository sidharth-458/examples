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
void intersection(int * a1, int s1, int *a2, int s2){
	qsort(a1,s1,sizeof(int),compare);
	qsort(a2,s2,sizeof(int),compare);
	int i = 0, j = 0;
	while((i<s1) && (j<s2)){
		if(a1[i] > a2[j])
			i++;
		else if ( a1[i] == a2[j]){
			printf("%d ",a1[i]);
			i++;
			j++;
		}
		else
			j++;
	}
	printf("\n");
	
}
int main(){
	int a1[] = {-INT_MAX, 1, -2, 3,5,-100,45,45,32,45,23,45};
	int a2[] = {-1, 2, 3,-5, -4, 6, -9, -10};
	intersection(a1,sizeof(a1)/sizeof(int), a2, sizeof(a2)/sizeof(int));
}
