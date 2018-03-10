#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main(int argc,char *argv[]){
	if(argc<2){
		 fprintf(stderr,"usage :%s dir",argv[0]);
		exit(1);
	}
	struct stat buf;
	struct dirent *Dirent;
	if(lstat(argv[1],&buf)<0){
		perror("lstat error");
		exit(1);
	}else{
		if(!S_ISDIR(buf.st_mode)){
		perror("not dir");
		exit(1);
		}else{
		DIR *dir = opendir(argv[1]);
		if(dir==NULL){
			perror("opendir error");
			exit(1);
		}else{
			while((Dirent = readdir(dir))!=NULL){
			printf("%-20s %ld\n",Dirent->d_name,Dirent->d_ino);
			}
		}
		}
	}
	return 0;
}
