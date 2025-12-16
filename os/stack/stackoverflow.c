#include<stdio.h>

#define STACKSIZE (16777216)

int main(){
	int sum = 0;
	char arr[ STACKSIZE ];
	for(int i = 0; i< STACKSIZE ; i++)
		sum += arr[i];
	printf("%d\n",sum);
	return 0;
}
