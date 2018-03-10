#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage %s file",argv[0]);
		exit(1);
	}
	int i = 1;
	for(;i<argc;i++){
		if(/*unlink(argv[i])*/remove(argv[i])){//對於文件unlink的功能等同與remove
			perror("unlink error");
			continue;
		}
	}
	printf("unlink sucessful\n");
	return 0;
}
