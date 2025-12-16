#include<string.h>
#include<stdio.h>

void rev(char *arr, int len){
	for(int i =0; i<len/2;i++){
		char temp = arr[len -i - 1];
		arr[len -i -1] = arr[i];
		arr[i] = temp;
	}
}

void word(char * arr){
	int len = strlen(arr);
	int id = 0;
	while( id < len){
		//skip spaces
		while(id < len && arr[id] == ' ')
			id++;
		//first letter
		int fid = id;
		char * fptr = arr + fid;

		//skip letters
		while(id < len && arr[id] != ' ')
			id++;
		//reverse word
		if(id < len)
			rev(fptr,id - fid);

		id++;
	}
	printf("%s\n",arr);
}
int main(){
	char arr[] = " hello   world i take this from you  ";
	printf("%s\n",arr);
	rev(arr,sizeof(arr) -1);
	printf("%s\n",arr);
	word(arr);
}
