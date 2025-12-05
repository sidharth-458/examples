#include<stdio.h>
#include<stdatomic.h>
#include<pthread.h>
atomic_int count = 0;
void * thread(void *){
	for(int i = 0; i<10000000;i++){
		//count = count +i;
		atomic_fetch_add(&count,i);
	}
	return NULL;
}

int main(){
	pthread_t t1,t2;
	pthread_create(&t1,NULL,thread,NULL);
	pthread_create(&t2,NULL,thread,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	printf("count %d\n",count);
	return 0;
}
