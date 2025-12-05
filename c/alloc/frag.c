#include<stdlib.h>
#include<stdio.h>

void * __real_malloc(size_t);
void * __wrap_malloc(size_t size){
	void * ptr = __real_malloc(size);
	if(!ptr)
		perror("malloc()");
	printf("allocation @%p of size %zu\n",ptr,size);
	return ptr;
}
void __real_free(void *);
void __wrap_free(void * ptr){
	if(!ptr)
		perror("free()");
	__real_free(ptr);
	printf("free'd @%p\n",ptr);
}
int main(){
	void * a,*b,*c;
	a = malloc(10);
	b = malloc(4);
	c = malloc(5);
	free(b);
	b = malloc(4);

	free(a);
	free(b);
	free(c);
}
