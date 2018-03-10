#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int d1;
	int d2;
}Arg;

void * th_fn(void *arg){
	Arg *r = (Arg *)arg;
	return (void *)r;
}
int main(void){
	pthread_t th;
	int err;
	Arg r = {10,60};
	if((err = pthread_create(&th,NULL,th_fn,&r))!=0){
		perror("pthread_create error");
	}
/*	int *result;
	pthread_join(th,(void **)&result);
	printf("result is %d\n",((Arg*)result)->d1+((Arg*)result)->d2);
*/
	int result;
	pthread_join(th,(void*)&result);
	printf("result is %d\n",((Arg *)result)->d1+((Arg *)result)->d2);
	return 0;
}
