#include"io_copy.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>

int main(int argc,char *argv[]){
	int fd_in = STDIN_FILENO;
	int fd_out = STDOUT_FILENO;
	int i = 1;
	for(;i<argc;i++){
	 if((fd_in = open(argv[1],O_RDONLY))<0){
 		perror("stdin:");
	 	continue;
	   }else{
		copy(fd_in,fd_out);
		exit(0);
		}
	}
	if(argc==1){
	copy(fd_in,fd_out);
	exit(0);
	}
	return 0;
}
