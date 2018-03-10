#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
void out_state(pthread_attr_t *attr){
	int state;
	if(pthread_attr_getdetachstate(attr,&state)!=0){
		perror("pthread_attr_getdetachstate error");
	}else{
		if(state==PTHREAD_CREATE_JOINABLE){
			printf("joinabale state\n");
		}else if(state==PTHREAD_CREATE_DETACHED){
			printf("detached state\n");	
		}else{
			printf("error state\n");
		}
		
	}
}
void * th_fn(void *arg){
	int i;
	int sum = 0;
	for(i=1;i<=100;i++){
		sum+=i;
	}
	printf("%lx occured\n",pthread_self());
	return (void*)sum;
}
int main(void){
	int err;
	pthread_t default_th,detach_th;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	out_state(&attr);
	if((err =pthread_create(&default_th,&attr,th_fn,(void *)0))!=0){
		perror("pthread create error");
	}
	int res;
	if((err = pthread_join(default_th,(void *)&res))!=0){
		perror("pthread join  error");
	}else{
		printf("default return si %d\n",(int)res);
	}
	printf("----------------------------------------------\n");
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	out_state(&attr);
	if((err=pthread_create(&detach_th,&attr,th_fn,(void*)0))!=0){
		perror("pthread create error");
	}	//如果線程的屬性是分離狀態則不能用pthread_join函數來啓動線程
/*	if((err = pthread_join(detach_th,(void *)&res))!=0){
		perror("pthread join  error");
	}else{
		printf("detach return si %d\n",(int)res);
	}
*/
	pthread_attr_destroy(&attr);
	printf("0x%lx finished\n",pthread_self());
	sleep(1);
	return 0;
}
