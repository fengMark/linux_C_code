#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<memory.h>
#include<stdlib.h>
int main(int argc,char *argv[]){
	if(argc<2){
		printf("usage :%s fifo \n",argv[0]);
		exit(1);
	}
	printf("open fifo read >>>\n");
	int fd =  open(argv[1],O_RDONLY);
	if(fd<0){
		perror("open error");
		exit(1);
	}else{
		printf("open file sucess:%d\n",fd);
	}
	char buf[512];
	memset(buf,0,sizeof(buf));
	while(read(fd,buf,sizeof(buf))<0){
		perror("read error");
	}
	printf("%s\n",buf);
	close(fd);
 	return 0;
}
