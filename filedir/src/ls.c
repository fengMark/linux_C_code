#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage :%s file",argv[0]);
		exit(1);
	}
	int i = 2;
	for(;i<argc;i++){
		if(link(argv[1],argv[i])==-1){
			perror("link error");
			continue;
		}
	}
	printf("sucessful create\n");
	return 0;
}
