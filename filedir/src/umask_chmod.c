#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define  UMASK S_IRUSR | S_IWGRP |S_IROTH |S_IXOTH

#define MODE  S_IRWXU | S_IRWXG | S_IRWXO
int main(int argc,char *argv[]){
	if(argc<2){
	fprintf(stderr,"usage :%s files",argv[0]);
	exit(1);
	}
	umask(UMASK);
/*	int fd = open(argv[1],O_WRONLY |O_CREAT|O_EXCL|O_TRUNC,MODE);
	if(fd<0){
		perror("open error");
		exit(1);
	}//被umask設置的權限不能再使用創建文件的權限上
*/      
	chmod(argv[1],MODE); //通過文件名稱更改文件權限
//	int fd = open(argv[1],O_WRONLY);
//	fchmod(fd,MODE);//通過文件描述副更改文件的權限
//	close(fd);
	return 0;
}
