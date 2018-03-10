#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<sys/msg.h>

int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage : %s file\n",argv[0]);
		exit(1);
	}
	int msqid = atoi(argv[1]);
	if(msgctl(msqid,IPC_RMID,NULL)<0){
		perror("msgctl error");
		exit(1);
	}
	exit(0);
}
