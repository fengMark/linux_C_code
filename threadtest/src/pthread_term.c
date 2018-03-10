#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
typedef struct{
	int d1;
	int d2;
}Arg;
void *th_fn(void *arg){
	Arg *r = (Arg *)arg;
	return (void *)(r->d1+r->d2);
}
int main(void){
	int err;
	pthread_t th;
	Arg r ={20,50};
	if((err = pthread_create(&th,NULL,th_fn,(void *)&r))!=0){
		perror("pthread_create error");
	}
/*	int *result;//指針變量裏面存結果
	pthread_join(th,(void **)&result);
	printf("reslut is %d\n",(int)result);
*/
	int result;
	pthread_join(th,(void*)&result);//變量地址存結果
	printf("result is %d\n",result);
	return 0;
}
