#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<memory.h>

int main(int argc,char *argv[]){
	if(argc<2){
	fprintf(stderr,"usage :%s files",argv[0] );
	exit(1);
	}
	int i;
	char *ptr;
 	struct stat buff;
	for(i=1;i<argc;i++){
	   memset(&buff,0,sizeof(buff));//各個成員變量初始化爲0
	   if(lstat(argv[i],&buff)<0){
	    perror("lstat error");
	    continue;
   	    }
	   printf("%-20s",argv[i]);//左對其
	if(S_ISREG(buff.st_mode)){
	    ptr = "normal file";
	}
	else if(S_ISDIR(buff.st_mode)){
	    ptr = "dir file";
	}
	else if(S_ISCHR(buff.st_mode)){
	    ptr = "character special file";
	}
	else if(S_ISBLK(buff.st_mode)){
	    ptr = "block file";
	}
	else if(S_ISFIFO(buff.st_mode)){
	    ptr = "fifo file";
	}
	else if(S_ISLNK(buff.st_mode)){
	    ptr = "symbolic link";
	}
    	else if(S_ISSOCK(buff.st_mode)){
	    ptr = "socket file";
	}
	else{
	    ptr = "unkown types";
	}
	printf("%s\n",ptr);
}
	return 0;
}
