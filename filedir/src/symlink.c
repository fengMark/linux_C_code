#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<memory.h>
int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage %s file",argv[0]);
		exit(1);
	}
	if(symlink(argv[1],argv[2])){
		perror("symlink error");
		exit(1);
	}
	int fd = open(argv[2],O_RDONLY);
	if(fd<0){
		perror("file open error");
		exit(1);
	}
	char buf[1024];
	ssize_t size;
	if((size = read(fd,buf,sizeof(buf)))<0){
		perror("read error");

	}
	else{
	write(STDOUT_FILENO,buf,sizeof(buf));
	}
	close(fd);
	printf("\n");
	memset(buf,0,sizeof(buf));
	if((size= readlink(argv[2],buf,sizeof(buf)))<0){
		perror("readlink error");
		exit(1);
	}
	else{
	write(STDOUT_FILENO,buf,size);
	}
	return 0;
}
