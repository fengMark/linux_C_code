#include<sys/shm.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"tell.h"
#include<sys/wait.h>
#include<unistd.h>
int main(void){
	int shmid;
	if((shmid = shmget(IPC_PRIVATE,1024,IPC_CREAT|IPC_EXCL|0777))<0){
		perror("shmget error");
		exit(1);
	}
	init();
	pid_t pid = fork();
	if(pid<0){
		perror("fork error");
		exit(1);
	}else if(pid>0){
		int *pi = (int *)shmat(shmid,0,0);
		if(pi==(int*)-1){
			perror("shmat error");
			exit(1);
		}
		*pi = 100;
		*(pi+1) = 200;
		shmdt(pi);
		notify_pipe();
		destory_pipe();
		wait(0);
	}else{
		wait_pipe();//子進程阻塞
		int *pi = (int *)shmat(shmid,0,0);
		if(pi==(int*)-1){
			perror("shmat error");
			exit(1);
		}
		printf("pi:%d,pi+1:%d\n",*pi,*(pi+1));
		shmdt(pi);
		destory_pipe();
		shmctl(shmid,IPC_RMID,NULL);
	}
}
