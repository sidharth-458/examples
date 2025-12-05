#include<stdio.h>

void array_rev(char * begin, char * end){
	int dist = begin -end;
	for(int i = 0; i<dist/2;i++){
		char temp = *(begin +i);
		*(begin + i) = *(end -1 - i);
		*(end -1 -i) = *(begin +i);
	}
	printf("%s\n",begin);
}

int main(){
	char * s = "hello";
	array_rev(s,s+4);
	printf("array_rev %s\n",s);
}
