#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>

int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage :%s file\n",argv[0]);
		exit(1);
	}
	int fd = open(argv[1],O_RDWR);
	if(fd<0){
   		perror("open error");
		exit(1);
	}
	lseek(fd,19,SEEK_END);
	write(fd,"0",1);
//	lseek(fd,0L,SEEK_SET);//can
	char *addr;
	addr = mmap(0,20,PROT_WRITE,MAP_SHARED,fd,0);
	if(addr < 0){
		perror("mmap error");
		exit(1);
	}
	int i = 0;
	for(;i<20;i++){
	 addr++;
	*addr = 'A'+i;
	}

        munmap(addr,0);
	
	close(fd);
	return 0;
}
