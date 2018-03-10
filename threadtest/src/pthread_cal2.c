#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
typedef struct{
	int res;
	int counter;//判斷條件
	pthread_cond_t cond;//條件變量
	pthread_mutex_t mutex;//互斥鎖
}Result;


void * set_fn(void *arg){
	int i=1,sum=0;
	for(;i<=100;i++){
		sum+=i;
	}
	Result *r = (Result *)arg;
	r->res=sum;
	pthread_mutex_lock(&r->mutex);
	while(r->counter<2){
		pthread_mutex_unlock(&r->mutex);
		usleep(100);
		pthread_mutex_lock(&r->mutex);
	}
	pthread_mutex_unlock(&r->mutex);
	pthread_cond_broadcast(&r->cond);
	
}
void * get_fn(void *arg){
	Result *r =(Result*)arg;
	pthread_mutex_lock(&r->mutex);
	r->counter++;

	pthread_cond_wait(&r->cond,&r->mutex);
	pthread_mutex_unlock(&r->mutex);
	int res = r->res;
	printf("0x%lx get sum is %d\n",pthread_self(),res);
	return (void*)0;
}
int main(void){
	int err;
	pthread_t cal,get1,get2,get3;
	Result r;
	r.counter = 0;
	pthread_cond_init(&r.cond,NULL);
	pthread_mutex_init(&r.mutex,NULL);
	if((err=pthread_create(&get1,NULL,get_fn,(void*)&r))!=0){
		perror("pthread create error");
	}
	
	if((err=pthread_create(&get2,NULL,get_fn,(void*)&r))!=0){
		perror("pthread create error");
	}
	
	if((err=pthread_create(&get3,NULL,get_fn,(void*)&r))!=0){
		perror("pthread create error");
	}
	if((err=pthread_create(&cal,NULL,set_fn,(void*)&r))!=0){
		perror("pthread create error");
	}
	pthread_join(cal,NULL);
	pthread_join(get1,NULL);
	pthread_join(get2,NULL);
	pthread_join(get3,NULL);
	pthread_cond_destroy(&r.cond);
	pthread_mutex_destroy(&r.mutex);
	return 0;
}
