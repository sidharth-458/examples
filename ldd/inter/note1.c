/*1100 0010 1011 0101
0011 0100 1101 1010
*/
#include<stdint.h>
#include<stdio.h>
struct a{
	uint16_t a:4;
	uint16_t b:4;
	uint16_t c:4;
	uint16_t d:4;
};
union ab{
	struct a nibs;
	uint16_t num;
};

struct a rev(struct a inp){
	int temp = 0;
	int cmp = inp.a;
	printf("%d\n",inp.a);
	for(int i = 0 ; i< 4;i++){
		printf("--%d %d\n",temp,cmp);
		temp = temp<<1;
		temp |= (cmp & 1);
		cmp = cmp>>1;
	}
	printf("%d\n",temp);
	inp.a = temp;

	temp = 0;
	cmp = inp.b;
	for(int i = 0 ; i< 4;i++){
		temp = temp<<1;
		temp |= (cmp & 1);
		cmp = cmp >>1;
	}
	inp.b = temp;

	temp = 0;
	cmp = inp.c;
	for(int i = 0 ; i< 4;i++){
		temp = temp<<1;
		temp |= (cmp & 1);
		cmp = cmp>>1;
	}
	inp.c = temp;

	temp = 0;
	cmp = inp.d;
	for(int i = 0 ; i< 4;i++){
		temp = temp<<1;
		temp |= (cmp & 1);
		cmp = cmp>>1;
	}
	inp.d = temp;
	return inp;
}
int main(){
	union ab inp;
	inp.num = 0x1234;
	printf("inp %x\n",inp.num);
	inp.nibs = rev(inp.nibs);
	printf("out %x\n",inp.num);
}
