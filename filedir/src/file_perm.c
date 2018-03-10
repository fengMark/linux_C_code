#include<unistd.h>
#include<sys/stat.h>
#include<memory.h>
#include<stdlib.h>
#include<stdio.h>


int main(int argc,char *argv[]){
	if(argc<2){
	 fprintf(stderr,"usage : %s files",argv[0]);
       	 exit(1);
	}
	struct stat buff;
	int i;
	mode_t mode;
	for(i=1;i<argc;i++){
		printf("%-20s",argv[i]);
		memset(&buff,0,sizeof(buff));
		if(lstat(argv[i],&buff)<0){
			perror("lstat error");
			continue;
		}
		mode = buff.st_mode;
//usr
		if(S_IRUSR & mode){
			printf("r");
		}else{
			printf("-");
		}
		if(S_IWUSR & mode){
			printf("w");
		}else{
			printf("-");
		}
		if(S_IXUSR & mode){
			printf("x");
		}else{
			printf("-");
		}
	//grp
		if(S_IRGRP & mode){
			printf("r");
		}else{
			printf("-");
		}
		if(S_IWGRP & mode){
			printf("w");
		}else{
			printf("-");
		}
		if(S_IXGRP & mode){
			printf("x");
		}else{
			printf("-");
		}
//other
		if(S_IROTH & mode){
			printf("r");
		}else{
			printf("-");
		}
		if(S_IWOTH & mode){
			printf("w");
		}else{
			printf("-");
		}
		if(S_IXOTH & mode){
			printf("x");
		}else{
			printf("-");
		}
		printf("\n");
	}
	return 0;
}
