#include<stdio.h>
#define BYTE(x,id) ((x & (0xff << id * 8))>> id *8 ) 
int endi(int n){
	printf("%x %x %x %x\n",BYTE(n,0),BYTE(n,1),BYTE(n,2),BYTE(n,3));
	n = BYTE(n,0) << 24 | BYTE(n,1) << 16 | BYTE(n,2) << 8 | BYTE(n,3);
	return n;
}
int main(){
	printf("%x\n",endi(0x1234abcd));
	
}
