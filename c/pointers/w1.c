#include<stdio.h>

void assign(){
	int a = 2;
	int * ptr = &a;
	printf("a %d, *ptr %d, ptr %p, &a %p\n",a,*ptr,ptr,&a);
}

void modify(){
	int a =2, *ptra;
	float b= 6.0,*ptrb;
	char c = 'c',*ptrc;
	ptra = &a;
	ptrb = &b;
	ptrc = &c;
	printf(" a %d, b %f, c %c\n",a,b,c); 
	printf(" &a %p, &b %p, &c %p\n",(void*)ptra,(void*)ptrb,(void*)ptrc);

	*ptra = 12;
	*ptrb = 3.03;
	*ptrc= '*';

	printf(" a %d, b %f, c %c\n",a,b,c); 
	printf(" &a %p, &b %p, &c %p\n",(void*)ptra,(void*)ptrb,(void*)ptrc);
}
void swap(int *a, int *b){
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}
void iterate(){
	int arr[] = {1,2,3,4,5};
	for(int i = 0;i<sizeof(arr)/sizeof(int);i++){
		printf("%d %d\n",arr[i],*(arr +i));
	}
}
void modarray(){
	int arr[] = {1,2,3,4,5};
	for(int i = 0;i<sizeof(arr)/sizeof(int);i++)
		printf("%d %d\n",arr[i],*(arr +i));
	for(int i = 0;i<sizeof(arr)/sizeof(int);i++)
		*(arr +i) += 1;


	for(int i = 0;i<sizeof(arr)/sizeof(int);i++)
		printf("%d %d\n",arr[i],*(arr +i));
}
void printarr(int arr[], int size){
	if(!arr)
		return;
	for(int i = 0;i<size;i++)
		printf("%d %d\n",arr[i],*(arr +i));

}
void nulltry(){
	int arr[] = {1,2,3,4,5};
	int *p = arr;
	printarr(p,sizeof(arr)/sizeof(int));
}
int printstack(){
	int a ;
	char b;
	int c;	
	printf("%p %p %p\n",(void*)&a,(void*)&b,(void*)&c);
}
void p2p(){
	int a = 5;
	int *p =&a;
	int **pp= &p;
	printf("%d %d %d\n",a,*p,**pp);
	printf("%p %p %p\n",(void*)&a,(void*)p,(void*)*pp);
	printf("%p %p\n",(void*)&p,(void*)pp);
	printf("%p\n",(void*)&pp);
}
char  *a = "hello world";
void fiddle(){
	char *p = a;
}
void garbage(){
	char *p;
	printf("%s",p);
}
void mismatch(){
	int a = 5;
	float * pf = (float*)&a;
}
int main(){
	assign();
	modify();

	int a = 5;
	int b = 10;
	printf("before %d,%d",a,b);
	swap(&a,&b);
	printf(":after %d,%d\n",a,b);
	
	iterate();
	modarray();
	nulltry();
	printstack();
	p2p();
	fiddle();
	garbage();
	mismatch();
}
