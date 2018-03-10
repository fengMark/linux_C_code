#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<sys/stat.h>

int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage :%s dir",argv[0]);
		exit(1);
	}
	struct stat buf;
	char buff[1024];
	if(lstat(argv[1],&buf)<0){
		perror("not dirent");
		exit(1);
	}else{
		if(getcwd(buff,sizeof(buff))==NULL){
			perror("getcwd error");
			exit(1);
		}
		printf("%s\n",buff);
		if(chdir(argv[1])<0){
			perror("change dir error");
			exit(1);
		}else{
			
			if(getcwd(buff,sizeof(buff))==NULL){
				perror("getcwd error");
				exit(1);
			}
			printf("%s\n",buff);
		}
	}


	return 0;
}
