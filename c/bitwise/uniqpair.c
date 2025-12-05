#include<stdio.h>
int arr[] = {1,3,4,5,3,1};

void uniq(int * arr, int sz){
	int xor = 0;
	int lastset = 0;
	int res1 = 0, res2 = 0;
	for(int i = 0;i<sz;i++)
		xor ^= *(arr + i);

	lastset = xor & (~xor + 1); // xor & (-xor);
	
	for(int i = 0;i<sz;i++){
		if(lastset & *(arr + i)){
			res1 ^= *(arr +i);
		}
		else{
			res2 ^= *(arr +i);
		}
	}
	printf("%d %d\n",res1,res2);

}

int main(){
	uniq(arr,6);
}
