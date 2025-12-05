#include<stdio.h>
#include<stdint.h>
#define and &
#define or |
#define start {
#define end }
#define u8 uint8_t
#define i64 int 
u8 rotate(u8 inp,i64 shift)
start
	u8 mask = 0;
	for(i64 i =0; i<8 - shift;i++)
	start
		mask = mask<<1;
		mask |= 1;
	end
	inp = ((inp and mask) << shift ) or ((inp and ~mask) >> 8 -shift);
	return inp;
end

int main(){
	uint8_t a = 0b10011100;
	printf("inp %08b\n",a);
	printf("out %08b\n",rotate(a,3));
}
