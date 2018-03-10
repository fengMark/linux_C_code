#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/types.h>
#include<string.h>

int main(int argc,char *argv[]){
	if(argc!=3){
	fprintf(stderr,"usage error %s\n",strerror(errno));
	exit(1);
	}
	int fdin;
	int fdout;
	fdin = open(argv[1],O_RDONLY);
	if(fdin<0)
	{
	perror("filein open error");
	exit(1);
	}
	fdout = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0777);
	if(fdout<0){
	perror("file out open error\n");
	exit(1);
	}
	copy(fdin,fdout);
	close(fdin);
	close(fdout);

	return 0;
}
