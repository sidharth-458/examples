#include<stdio.h>
#include<stdbool.h>

bool isana(int a){
	int count = 0;
	for(; a!=0 ; a>>=1){
		if(a & 1)
			count++;
	}
	return count == sizeof (int) * 4;
}	
int main(){
	int a = 131070;
	printf("%d\n",isana(a));
}
