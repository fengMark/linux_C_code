#include"io.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
int main(int argc,char *argv[]){

	if(argc<4){
	perror("argument error");
	exit(1);
	}
	ssize_t size = strlen(argv[1])*sizeof(char);
	int fd = open(argv[2],O_WRONLY|O_CREAT,0777);
	if(fd<0){
		perror("open error");
		exit(1);
	}
	sleep(5);
	if(!strcmp("lock",argv[3])){
		WRITE_LOCKW(fd,0,SEEK_SET,0);
	}
	printf("lock success\n");
	printf("lock pid: %d\n",getpid());
	
	char *p = argv[1];
	int i;
	for(i=0;i<size;i++){
		if(write(fd,(p+i),1)!=1){
  		perror("write error");
		exit(1);
	}
	printf("%d sucess write one character\n",getpid());
	sleep(1);
	}
	if(!strcmp("lock",argv[3])){
		UNLOCK(fd,0,SEEK_SET,0);
		printf("unlock sucess:");
		printf("pid:%d\n",getpid());

	}
	close(fd);
	return 0;
}
