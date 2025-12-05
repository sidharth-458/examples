#include<stdio.h>

int miss(int * arr,int n){
	int xor_range = 0;
	int xor_array = 0;
	for(int i = 1;i<=n + 1;i++)
		xor_range ^= i;
	for(int i =0;i<n;i++)
		xor_array ^= arr[i];
	printf("xor_array %d\n",xor_array);
	printf("xor_range %d\n",xor_range);
	return xor_array ^ xor_range;
}

int main(){
	int arr[] = {1,2,3,4,5};
	printf("%d\n",miss(arr,5));
	return 0;
}
