#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void sig_handler(int signo){
	printf("pthread id in the sig_handler:%lx\n",pthread_self());
	if(signo==SIGALRM){
		printf("timeout .....\n");
	}
	alarm(2);
}

void * th_fn(void *arg){
	if(signal(SIGALRM,sig_handler)==SIG_ERR){
		perror("signal sigalrm error");
	}
	alarm(2);
	int i;
	for(i=1;i<=100;i++){
		printf("(0x%lx) i : %d\n",pthread_self(),i);
		sleep(1);
	}
	return (void *)0;
}
void *th2_fn(void *arg){
	pthread_t th1 = (pthread_t)arg;
	int i;
	for(i=1;i<=15;i++){
		if(i==5){
			pthread_cancel(th1);
			alarm(0);
		}
		printf("(%lx) i:%d\n",pthread_self(),i);
		sleep(1);
	}
	return (void*)0;
}
int main(void){
	int err;
	pthread_t th,th2;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	if((err=pthread_create(&th,&attr,th_fn,(void*)0))!=0){
			perror("pthread create error");
	}
	
	if((err=pthread_create(&th2,&attr,th2_fn,(void*)th))!=0){
			perror("pthread create error");
	}
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGALRM);
	//對主控線程屏蔽SIGALRM信號
	pthread_sigmask(SIG_SETMASK,&set,NULL);
	while(1){
		printf("control thread(%lx) is running \n",pthread_self());
		sleep(10);
	}
	printf("control thread over\n");
	return 0;
}
