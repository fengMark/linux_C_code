#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
char *buf = "0123456789";

int main(int argc,char *argv[]){
	if(argc<2){
	fprintf(stderr,"usage error:%s\n",strerror(errno));
	exit(1);
	}
  	int fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0777);
	if(fd<0){
	fprintf(stderr,"file open error:%s\n",strerror(errno));
	exit(1);
	}
	ssize_t size = strlen(buf)+sizeof(char);
	if(write(fd,buf,size)!=size){
	perror("write error\n");
	exit(1);
	}
	//定義到文件的尾部
	if(lseek(fd,10L,SEEK_END)<0){
	perror("lseek error\n");
	exit(1);
	}
        if(write(fd,buf,size)!=size){
        perror("write error\n");
        exit(1);
        }

	return 0;
}
