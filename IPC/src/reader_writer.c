#include<sys/shm.h>
#include<sys/sem.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
typedef struct{
	int val;
	int semid;
}Storage;
void sig_handler(int signo){
	waitpid(-1,NULL,WNOHANG);
}
void init(Storage *s){
	assert(s!=NULL);
	if((s->semid=semget(IPC_PRIVATE,2,IPC_CREAT|IPC_EXCL|0777))<0){
		perror("semget error");
		exit(1);
	}
	union semun{
		int 	val;
		struct semid_ds *ds;
		unsigned short *array;
	};
	union semun un;
	unsigned short array[2] = {0,0};
	un.array = array;
	if(semctl(s->semid,0,SETALL,un)<0){
		perror("semctl error");
		exit(1);
	}

}
void destory(Storage *s){
	assert(s!=NULL);
	if(semctl(s->semid,0,IPC_RMID,NULL)<0){
		perror("semctl error");
		exit(1);
	}

}
void writes(Storage *s,int val){
	s->val = val;
	printf("%d write %d\n",getpid(),val);
	//設置0號信號量s1做V(1)操作
	struct sembuf ops_v[1] = {{0,1,SEM_UNDO}};
	//設置1號信號量s2做p（1）操作
	struct sembuf ops_p[1] = {{1,-1,SEM_UNDO}};
	//v(s1)
	if(semop(s->semid,ops_v,sizeof(ops_v)/sizeof(struct sembuf))<0){
		perror("semop error");
	}	
	//p(s2)
	
	if(semop(s->semid,ops_p,sizeof(ops_p)/sizeof(struct sembuf))<0){
		perror("semop error");
	}	
}
void reads(Storage *s){
	assert(s!=NULL);
	//設置0號信號量s1做p1操作
	struct sembuf ops_p[1] = {{0,-1,SEM_UNDO}};
	//設置1號信號量s2做v1操作
	struct sembuf ops_v[1] = {{1,1,SEM_UNDO}};
	//P(s1);
	if(semop(s->semid,ops_p,sizeof(ops_p)/sizeof(struct sembuf))<0){
		perror("semop error");
	}
	printf("%d read %d \n",getpid(),s->val);
	//V(s2);
	if(semop(s->semid,ops_v,sizeof(ops_v)/sizeof(struct sembuf))<0){
		perror("semop error");
	}
}
int main(void){
	if(signal(SIGCHLD,sig_handler)==SIG_ERR){
		perror("signal error");
	}
	int shmid;
	if((shmid = shmget(IPC_PRIVATE,sizeof(Storage),IPC_CREAT|IPC_EXCL|0777))<0){
		perror("shmget error");
		exit(1);
	}
	Storage *s = (Storage*)shmat(shmid,0,0);
	if(s==(Storage*)-1){
		perror("shmat error");
		exit(1);
	}
	init(s);
	pid_t pid;
	pid = fork();
	if(pid<0){
		perror("fork error");
		exit(1);
	}else if(pid>0){
		int i = 1;
		for(;i<=100;i++){
			writes(s,i);
		}
		destory(s);
		shmdt(s);
		shmctl(shmid,IPC_RMID,NULL);
	}else{
		int i= 1;
		for(;i<=100;i++){
			reads(s);
		}
		shmdt(s);
	}
	exit(0);
}
