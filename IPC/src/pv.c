#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sem.h>
#include"pv.h"
#include<string.h>
#include<malloc.h>
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
//創建信號量集，並初始化semnums個信號燈/信號量的值（value）
int I(int semnums,int value){
	//創建信號量集
	int semid = semget(IPC_PRIVATE,semnums,IPC_CREAT|IPC_EXCL|0777);
	if(semid<0){
		return -1;
	}
	union semun un;
	unsigned short *array = (unsigned short *)calloc(semnums,sizeof(unsigned short));
	int i;
	for(i=0;i<semnums;i++){
		array[i] = value;
	}
	un.array = array;
	//初始化信號量集中所有信號燈的初值
	if(semctl(semid,0,SETALL,un)<0){
		perror("semctl error");
		return -1;
	}
	free(array);
	return semid;
	

}
//對信號量集（semid）中的信號燈（semnum）做p(value)操作
void P(int semid,int senum,int value){
	assert(value>=0);
	struct sembuf ops[] = {{senum,-value,SEM_UNDO}};

	if(semop(semid,ops,sizeof(ops)/sizeof(struct sembuf))<0){
		perror("semop error");
	}
}
//對信號集（semid）中的信號燈（semnum）做v(value)操作
void V(int semid,int senum,int value){
	
	assert(value>=0);
	struct sembuf ops[] = {{senum,value,SEM_UNDO}};

	if(semop(semid,ops,sizeof(ops)/sizeof(struct sembuf))<0){
		perror("semop error");
	}

}

void D(int semid){
	if(semctl(semid,0,IPC_RMID,NULL)<0){
		perror("semctl error");
	}
}

