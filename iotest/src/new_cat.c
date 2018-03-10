#include"io_copy.h"
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

int main(int argc,char *argv[]){
	int fdin = STDIN_FILENO;
	int fdout=STDOUT_FILENO;
	int flag;
	int newfd;
	if(strcmp(argv[1],"+")==0){
		flag = 0;
		if((newfd = open(argv[2],O_WRONLY))<0){
			perror("file name or destinery failed\n");
			exit(1);
		}
		if(dup2(fdin,newfd)!=newfd){
			perror("dup2 fdin and newfd error\n");
			exit(1);
		}
	}
	if(strcmp(argv[1],"-")==0){
		flag = 0;
		if((newfd = open(argv[2],O_RDONLY))<0){
			perror("file name or destinery failed\n");
			exit(1);
		}
		if(dup2(fdout,newfd)!=newfd){
			perror("dup2 fdout and newfd error\n");
			exit(1);
		}
	}else{
		if(argc>1){
			flag = 1;
			int i=1;
			for(;i<argc;i++){
				if((newfd = open(argv[i],O_RDONLY))<0){
					perror("file is not exeits or faild dest");
					copy(newfd,fdin);
					close(newfd);
					continue;
				}
			}
		}
	}
    	if(!flag){
		copy(STDIN_FILENO,STDOUT_FILENO);
	}
	

}
