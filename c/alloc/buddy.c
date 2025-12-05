#include<stdint.h>
#include<stdio.h>
char arena[64];
uint64_t freelist;

#define BIT_SET(x,n) (x & (1 << n))

size_t nearest(size_t v){
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}
char * alloc(size_t size){
	if(!size || size>64){
		printf("no mem\n");
		return 0;
	}
	for(int i = 0; i< 64;i++){
		if(!BIT_SET(freelist,i)){
			for(int j = i;j<size+i && j<64;j++){
				if(BIT_SET(freelist,j)){
					i = j;
					break;
				}
			}
			if(j == size + i){
				return &arena[j];
			}
		}
	}

}

void free(char * ptr){
}
int main(){
	alloc(61);
}
