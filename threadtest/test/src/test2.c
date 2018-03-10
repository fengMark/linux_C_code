#include<phtread.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
typedef struct{
	int value;
	pthread_mutex_t rm;
	pthread_cond_t rc;
	int is_wait;

	pthread_mutex_t wm;
	pthread_cond_t wc;
	int counter;
}Storage;
void set_data(Storage *s,int value){
	s->value = value+100;
}
int get_data(Storage *s){
	return s->value;
}
void* set_fn(void* arg){
	Storage *s = (Storage *)arg;
	int i=1;
	for(;i<=100;i++){
		set_data(s,i);
		printf("(0x%lx) put data %d\n",pthread_self(),i);
		pthread_mutex_lock(&s->rm);
		while(s->counter<3){
			pthread_mutex_unlock(&s->rm);
			usleep(100);
			pthread_mutex_lock(&s->rm);
		}
		s->counter=0;
		pthread_mutex_unlock(&s->rm);
		pthread_cond_broadcast(&s->rc);
	//寫者進程等待讀者進程讀完	
		pthread_mutex_lock(&s->wm);
		s->is_wait=1;
		pthread_cond_wait(&s->wc,&s->wm);
		pthread_mutex_lock(&s->wm);
	}
	return (void*)0;
}
void* get1_fn(void* arg){
	Storage *s=(Storage *)arg;
	int i=1;
	int value;
	for(;i<=100;i++){
		pthread_mutex_lock(&s->rm);
		s->counter++;
		pthread_cond_wait(&s->rc,&s->rm);
		pthread_mutex_unlock(&s->rm);
		value = get_data(s);
		printf("(0x%lx) get data :%d\n",pthread_self(),value);
		//讀者進程等待寫者進程寫完
		pthread_mutex_lock(&s->wm);	
		while(!s->is_wait){
			pthread_mutex_unlock(&s->wm);
			sleep(1);
			pthread_mutex_lock(&s->wm);
		}
		s->is_wait=0;
		pthread_mutex_unlock(&s->wm);
		pthread_cond_broadcast(&s->wc,&s->wm);
	}
	return (void*)0;
}
void* get2_fn(void *arg){
	Storage *s=(Storage *)arg;
	int i=1;
	int value;
	for(;i<=100;i++){
		pthread_mutex_lock(&s->wm);
		s->counter++;
		pthread_cond_wait(&s->wc,&s->wm);
		pthread_mutex_unlock(&s->wm);
		value = get_data(s);
		printf("(0x%lx) get data :%d\n",pthread_self(),value);
		pthread_mutex_lock(&s->wm);	
		while(!s->is_wait){
			pthread_mutex_unlock(&s->wm);
			sleep(1);
			pthread_mutex_lock(&s->wm);
		}
		pthread_mutex_unlock(&s->wm);
		pthread_cond_broadcast(&s->wc,&s->wm);
	}
	return (void*)0;
}
void* get3_fn(void *arg){
	Storage *s=(Storage *)arg;	
	int i=1;
	int value;
	for(;i<=100;i++){
		pthread_mutex_lock(&s->wm);
		s->counter++;
		pthread_cond_wait(&s->wc,&s->wm);
		pthread_mutex_unlock(&s->wm);
		value = get_data(s);
		printf("(0x%lx) get data :%d\n",pthread_self(),value);
		pthread_mutex_lock(&s->wm);	
		while(!s->is_wait){
			pthread_mutex_unlock(&s->wm);
			sleep(1);
			pthread_mutex_lock(&s->wm);
		}
		pthread_mutex_unlock(&s->wm);
		pthread_cond_broadcast(&s->wc,&s->wm);
	}
	return (void*)0;
}
int main(void){
	int err;
	pthread_t set,get1,get2,get3;
	Storage s;
	s.value = 0;
	s.is_wait=0;
	s.counter=0;
	pthread_cond_init(&s.rc,NULL);
	pthread_mutex_init(&s.rm,NULL);
	pthread_cond_init(&s.wc,NULL);
	pthread_mutex_init(&s.wm,NULL);
	if((err=pthread_create(&set,NULL,set_fn,(void*)s))!=0){
		perror("pthread create error");
	}
	
	if((err=pthread_create(&get1,NULL,get1_fn,(void*)s))!=0){
		perror("pthread create error");
	}
	if((err=pthread_create(&get2,NULL,get2_fn,(void*)s))!=0){
		perror("pthread create error");
	}
	if((err=pthread_create(&get3,NULL,get3_fn,(void*)s))!=0){
		perror("pthread create error");
	}
	pthread_join(&set);
	pthread_join(&get1);
	pthread_join(&get2);
	pthread_join(&get3);
	pthread_cond_destroy(&rc);
	pthread_cond_destroy(&wc);
	pthread_mutex_destroy(&rm);
	pthread_mutex_destroy(&wm);
	return 0;
}
