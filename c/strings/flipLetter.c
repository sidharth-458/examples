#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
void flip(char * arr){
	int len = strlen(arr);
	for(int i = 0;i<len;i++){
		if(arr[i] >= 'A' && arr[i] <= 'z'){
			if(arr[i] >= 'a'){
				arr[i] = arr[i] - ( 'a' - 'A');
			}
			else{
				arr[i] = arr[i] + ( 'a' - 'A');
			}
		}
	}
}
int main(){
	char arr[] = "Hello, My name is Sidharth Seela";

	printf("%s\n",arr);
	flip(arr);
	printf("%s\n",arr);
}
