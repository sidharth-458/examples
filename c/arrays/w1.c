#include<stdbool.h>
#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
void print(int *arr , int size){
	for (int i = 0; i<size; i++)
		printf("%d\n",*(arr +i));
}
int sum(int * arr, int size){
	int ret = 0;
	for(int i = 0;i<size;i++)
		ret += *(arr +i);
	return ret;
}
int max(int *arr, int size){
	int max = - INT_MAX;
	for(int i = 0; i<size;i++){
		if (*(arr +i) > max)
			max = *(arr +i);
	}
	return max;
}

int min(int *arr, int size){
	int min = INT_MAX;
	for(int i = 0; i<size;i++){
		if (*(arr +i) < min)
			min = *(arr +i);
	}
	return min;
}
int odds(int * arr, size_t size){
	int odds = 0 ;
	for (int i =0; i<size;i++){
		if(*(arr +i) %2)
			odds++;
	}
	return odds;
}
void copy(int * dest, int * src, int size){
	if(!dest)
		exit(-1);
	if(!src)
		exit(-1);
	if(size <= 0 )
		return;
	
	for(int i = 0; i<size;i++)
		*(dest + i) = * (src + i);

}
int negs(int * arr, size_t size){
	int negs = 0;
	for(int i = 0; i<size;i++){
		if(*(arr +i) < 0)
			negs++;
	}
	return negs;
}
int find(int * arr, size_t size, int find){
	for(int i = 0; i< size;i++){
		if(find == *(arr +i))
			return i;
	}
	return -1;
}
int rev(int * arr,size_t size){
	int temp;
	for (int i = 0 ; i< size/2 ;i++){
		temp = *(arr +i);
		*(arr +i) = *(arr + size -i -1);
		*(arr + size -i -1) = temp;
	}
}
void insert(int * arr, size_t size,int insert,int pos){
	if(!arr)
		exit(-1);
	arr = realloc(arr,(size + 1)* sizeof(int));
	if(!arr)
		exit(-1);
	for(int i = size - 1 ;i>= pos;i--)
		*(arr +i +1) = *(arr +i);
	*(arr + pos) = insert;
}
void delete(int * arr, size_t size, int delpos){
	if(!arr)
		exit(-1);
	for(int i = delpos ;i<size -1;i++)
		*(arr + i) = * (arr + i +1);
	arr = realloc(arr,sizeof(int) * (size-1));
}
void swap(int * one, int * two){
	*one = *one ^ *two;
	*two = *one ^ *two;
	*one = *one ^ *two;
}
void asc(int * arr, int size){
	bool swapped;
	do{
		swapped = false;
		for(int i = 0; i<size -1;i++){
			if(*(arr + i) > *(arr +i + 1)){
				swap(arr +i, arr + i +1);
				swapped = true;
			}
		}
	}while(swapped);
}
void des(int * arr, int size){
	bool swapped;
	do{
		swapped = false;
		for(int i = 0; i < size -1 ; i++){
			if(*(arr + i) < * (arr +i +1)){
				swap(arr+i,arr+i+1);
				swapped = true;
			}
		}
	}while(swapped);
}

int main(){
	int arr[] = {-5,5,4,1,0};
	print(arr,5);
	printf("sum %d\n",sum(arr,5));
	printf("min %d, max %d\n",min(arr,5),max(arr,5));
	
	int *arr2 = malloc(sizeof(int) *5);
	copy(arr2,arr,5);
	print(arr2,5);
	
	int odd = odds(arr,5);
	printf("odds %d, even %d\n", odd, 5 -odd);

	printf("negs %d\n",negs(arr,5));
	printf("find -1 %d\n",find(arr,5,-1));

	rev(arr,5);
	print(arr,5);
	
	insert(arr2,5,10,3);
	print(arr2,6);

	delete(arr2,6,3);
	print(arr2,5);

	int arr3[]= { -5,5,4,1,0};
	asc(arr3,5);
	printf("sorted arr\n");
	print(arr3,5);

	printf("sorted down arr\n");
	des(arr3,5);
	print(arr3,5);
}
