#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#define REG_BASE 0x40000000
volatile uint32_t *reg_modifiable = (uint32_t *)REG_BASE;
const uint32_t *reg_readonly = (const uint32_t *)REG_BASE;
const volatile uint32_t *reg_const_volatile = (const volatile uint32_t *)REG_BASE;
void size(){
	int arr[] = {1,2,3,4,5},*p;
	p = arr;
	* p = 5;
	* (p+1) = 4;
	printf("%d %d\n",*p,*(p++));
	printf("%zu,%zu\n",sizeof(&arr),sizeof(p));
};
void print2d(){
	int arr[3][3] = { {1,2,3},{4,5,6},{7,8,9}};
	int *p =(int *) arr;
	for(int i = 0; i<9;i++){
		printf("%d\n",*(p +i));
	}
}
void modify(){
	*reg_modifiable = 2;
//	*reg_readonly = 4;
//	*reg_const_volatile = 5;
}
void memcopy(){
	int arr[] = {1,2,3,4,5};
	int *p = malloc(sizeof(int ) * 5);
	memcpy(p,arr,sizeof(int )*5);
}
struct __attribute__((packed))Per {
	char status;
	int control;
	short error;
};
void printstruct(){
	printf("%zu, %zu,%zu,%zu\n",offsetof(struct Per,status),offsetof(struct Per,control),offsetof(struct Per,error),sizeof(struct Per));
}
void  entry(void){
	printf("entry\n");
}
void  running(void){
	printf("runnning\n");
}
void  end(void){
	printf("end\n");
}
void (*pfn[])(void) = {entry,running,end};

int dangling(){
	int * mal = malloc(100);
	free(mal);
	*(mal + 99) = 3;
	printf("%d\n",*(int*)(mal +99));
}
int dyna2d(){
	int **reg;
	reg = malloc(3 * sizeof(int *));
	for(int i = 0 ; i<3;i++)
		reg[i] = malloc(3*sizeof(int));
	for(int i = 0; i<3;i++){
		for(int j = 0; j<3;j++){
			*(*(reg + i) + j )= i*j;
			printf("%d\n",reg[i][j]);
		}
	}
	for(int i = 0 ; i<3;i++)
		free(*(reg + i));
	
}
typedef int (*CalibArrayPtr)[10];
int arr[10];

CalibArrayPtr get_calibration_data(void){
	CalibArrayPtr a = (CalibArrayPtr) arr;
	return a;
}

struct Peripheral {
	uint8_t status;
	uint8_t control;
	uint16_t data;
};
struct Peripheral peris[5];
int main(){
/*	size();
	print2d();
	memcopy();
	printstruct();
	(*pfn)();
	pfn[1]();
	pfn[2]();

	dangling();
*/
	dyna2d();
	CalibArrayPtr ptr = get_calibration_data();
	struct Peripheral * ptrper = peris;
	printf("4th data %d\n", (*(ptrper + 3)).data);

}


