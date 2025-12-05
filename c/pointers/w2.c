#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
void dyn_basic(){
	int * a = malloc(sizeof(*a));
	float * b = malloc(sizeof(*b));
	*b = 3.14;
	printf("%d\n",(int)*((char *)a + 130000));
}
void revarr(int arr[],int size){
	int temp;
	for(int i = 0 ; i<size/2;i++){
		temp = *(arr + i);
		*(arr +i) = *(arr + size - 1);
		*(arr + size -1) = temp;
	}
}
void reversal(){
	int arr[] = {3,4,5,6,7};
	int * pta = malloc(sizeof(int) * 5);
	revarr(arr,sizeof(arr)/sizeof(int));
	revarr(pta,5);
}
void edit_word(int arr[]){
	char **p = (char **)&arr;
	*(*p) =1;
	*(*p + 1) = 1;
	*(*p + 2) = 1;
	*(*p + 3) = 1;
	
}
void dubptr(){
	char *m = malloc(sizeof(char ) * 4);
	edit_word((int *)m);
	printf("%x\n",*(int *)m);

}
struct abc{
	int a;
	char  b;
	long c;
};

void update(struct abc * a){
	a->a = 1;
	a->b = '2';
	a->c = 3;
}
	
void allocs(){
	int * arr = malloc(sizeof(int));
	if(!arr)
		exit(-1);
	arr = realloc(arr,sizeof(int) * 2);
	if(!arr)
		exit(-1);
	*arr = 0;
	*(arr + 1) = 1;
	printf("%d %d\n",arr[0],arr[1]);
	free(arr);
}
void strings(){
	char * str1 = "hello world";
	char * str2;
	str2 = malloc(20);
	if(!str2)
		exit(-1);
	strcpy(str2,str1);
	for(int i = 0; i< strlen(str2);i+=2)
		*(str2 + i) = '-';
	printf("%s %s\n",str1,str2);
}
int files(){
	int rfd = open("hello.txt",O_RDONLY);
	if(rfd == -1){
		perror("open");
		exit(-1);
	}
	int wfd = open("bye.txt",O_WRONLY);
	if(wfd == -1){
		perror("open");
		exit(-1);
	}
	int size = lseek(rfd,0,SEEK_END);
	lseek(rfd,0,SEEK_SET);
	printf("%d\n",size);
	char * arr = malloc(size);
	if(!arr){
		perror("malloc");
		close(rfd);
		close(wfd);
		exit(-1);
	}
	printf("read %zu\n",read(rfd,arr,size));
	printf("writtend %zu\n",write(wfd,arr,size));
	close(rfd);
	close(wfd);
}
int recursum(int * a, int next){
	if(next == 1)
		return *a;
	return *a + recursum(++a,--next);
}
void stringrev(char *s){
	if(*s == 0)
		return;
	stringrev(++s);
	printf("%c",*s);
}
int main(){
/*	dyn_basic();
	reversal();
	dubptr();
	
	struct abc * a = malloc(sizeof(*a));
	update(a);
	allocs();
	strings();

	files();
*/
	int arr[] = {1,2,3,4,5};
	printf("%d\n",recursum(arr,5));
	char * str = "helloworld";
	stringrev(str);
}

