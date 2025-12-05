#include<stdio.h>

int odd_occur(int * arr, int sz){
	int res;
	for(int i = 0 ; i < sz ; i++){
		res ^= arr[i];
	}
	return res;
}

int main(){
	int arr[] = {1,1,2,2,3,4,4};
	printf("%d\n",odd_occur(arr,sizeof(arr)/sizeof(int)));
}
