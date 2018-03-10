#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
void *th_fn(void *arg){
	
	int distance = (int)arg;
	int i;
	for(i=1;i<=distance;i++){
		printf("%lx run %d\n",pthread_self(),i);
		int time =(int)(drand48()*100000);
		usleep(time);
	}
	return (void *)0;
}


int main(void){
	int err;
	pthread_t rabbit,turtle;
	if((err = pthread_create(&rabbit,NULL,th_fn,(void *)50))!=0){
		perror("pthread _creat error");
	}
	
	if((err = pthread_create(&turtle,NULL,th_fn,(void *)50))!=0){
		perror("pthread _creat error");
	}
	//主控縣城調用pthread——join自己會阻塞
	//直到rabbit和turtle縣城運行結束方可運行
	pthread_join(rabbit,NULL);
	pthread_join(rabbit,NULL);
//	sleep(10);
	printf("control thread id: %lx\n",pthread_self());
	printf("finished\n");
	return 0;
}
