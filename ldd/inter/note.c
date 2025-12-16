#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char str[] = "I am an embedded engineer";
/*a - 2
m - 2
n - 3
e - 6
*/
char arr[256] = {0};
struct id{
	char val;
	int count;
};
int main(){
	struct id * real = NULL;
	int total = 0;
	for(int i = 0;i<strlen(str);i++){
		if(*(str + i) != ' ')
			arr[*(str + i)]++;
	}
	for(int i = 0;i<256;i++){
		if(arr[i]){
			total++;
			real = reallocarray(real,sizeof(struct id),total);
			real[total - 1].val = i;
			real[total - 1].count = arr[i];
		}
	}
	for(int i = 0;i<total;i++){
		for(int j = i; j < total;j++){
			if(real[i].count > real[j].count){
				int count = real[j].count;
				int val = real[j].val;
				real[j].count = real[i].count;
				real[j].val = real[i].val;
				real[i].count = count;
				real[i].val = val;
			}
		}
	}
	for(int i = total - 1;i >=0;i--){
		printf("%c : %d\n",real[i].val,real[i].count);
	}
}
