#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
sem_t sem1;
sem_t sem2;
sem_t sem3;
sem_t sem4;
void *a_fn(void *arg){
	int i =10;
	while(i){	
		sem_wait(&sem1);
		printf("(0x%lx) a is running\n",pthread_self());
		sem_post(&sem4);	
		printf("(0x%lx) a is running\n",pthread_self());
		i--;
	}
	return (void*)0;
}
void *b_fn(void *arg){
	int i =10;
	while(i){
		sem_wait(&sem2);
		printf("(0x%lx) b is running\n",pthread_self());
		sem_post(&sem1);
		sem_wait(&sem4);	
		printf("(0x%lx) b is running\n",pthread_self());
		sem_post(&sem3);
		i--;
	}
	return (void*)0;
} 
void *c_fn(void *arg){
	int i =10;
	while(i){
		sem_post(&sem2);
		printf("(0x%lx) c  is running\n",pthread_self());
		sem_wait(&sem3);				
		printf("(0x%lx) c  is running\n",pthread_self());
		i--;
	}
	return (void*)0;
}
int main(void){
	pthread_t a,b,c;
	int err;
	sem_init(&sem1,0,0);
	sem_init(&sem2,0,0);
	sem_init(&sem3,0,0);
	sem_init(&sem4,0,0);
	if((err=pthread_create(&a,NULL,a_fn,(void*)0))!=0){
		perror("pthread create error");
	}	
	if((err=pthread_create(&b,NULL,b_fn,(void*)0))!=0){
		perror("pthread create error");
	}
	if((err=pthread_create(&c,NULL,c_fn,(void*)0))!=0){
		perror("pthread create error");
	}
	pthread_join(a,NULL);
	pthread_join(b,NULL);
	pthread_join(c,NULL);
	sem_destroy(&sem1);
	sem_destroy(&sem2);	
	sem_destroy(&sem3);
	sem_destroy(&sem4);
	return 0;
}
