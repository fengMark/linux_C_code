#include<sys/sem.h>
#include<malloc.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int  I(int semnums,int val){
	int semid = semget(IPC_PRIVATE,semnums,IPC_CREAT|IPC_EXCL|0777);
	if(semid<0){
		perror("semget error");
		exit(1);
	}
	union semun un;
	unsigned short *array = (unsigned short *)calloc(semnums,sizeof(unsigned short));	
	int i = 0;
	for(;i<semnums;i++){
		array[i] = val;
	}
	un.array = array;
	if(semctl(semid,0,SETALL,un)<0){
		perror("semctl error");
		exit(1);
	}
	free(array);
	return semid;
}
void P(int semid,unsigned short sem_num,short value){
	assert(value>=0);
	struct sembuf ops[] = {{sem_num,-value,SEM_UNDO}};
	if(semop(semid,ops,sizeof(ops)/sizeof(struct sembuf))<0){
		perror("semop error");
	}
}
void V(int semid,unsigned short sem_num,short value){
	
	struct sembuf ops[] = {{sem_num,value,SEM_UNDO}};
	if(semop(semid,ops,sizeof(ops)/sizeof(struct sembuf))<0){
		perror("semop error");
	}
}
void D(int semid){
	if(semctl(semid,0,IPC_RMID,NULL)<0){
		perror("semctl error");
		exit(1);
	}

}

