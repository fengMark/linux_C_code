#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<string.h>
#include<sys/types.h>
#include<stdio.h>


int main(int argc,char *argv[]){
	if(argc<3){
	printf("usage :%s srcfile destfile\n",argv[0]);
	exit(1);
	}

	int sfd = open(argv[1],O_RDONLY);
	if(sfd<0){
	perror("open error");
	exit(1);
	}
	int dfd = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0777);
	if(dfd<0){
	perror("open error");
	exit(1);
	}
	off_t len = lseek(sfd,0,SEEK_END);
	printf("s file length:%ld\n",len);
	lseek(dfd,len-1,SEEK_SET);
	write(dfd,"0",1);
   	char *a1 = mmap(0,len,PROT_READ,MAP_SHARED,sfd,0);
	if(a1<0){
	perror("mmap error");
	exit(1);
	}
 	char *a2 = mmap(0,len,PROT_READ,MAP_SHARED,dfd,0);
	if(a2<0){
	perror("mmap error");
	exit(1);
	}
	memcpy(a2,a1,len);
	munmap(a2,0);
	munmap(a1,0);
	close(sfd);
	close(dfd);
 	return 0;
}
