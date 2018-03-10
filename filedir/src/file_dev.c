#include<unistd.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<memory.h>
#include<fcntl.h>
#include<sys/types.h>
void out_dev(dev_t devno){
	printf("%5d,%5d\n",major(devno),minor(devno));
}

int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage : %s file",argv[0]);
		exit(1);
	}
	int i=1;
	struct stat buf;
	for(;i<argc;i++){
		memset(&buf,0,sizeof(buf));
		if(lstat(argv[i],&buf)<0){
			perror("lstat error");
			exit(1);
		}else{
			if(S_ISCHR(buf.st_mode)||S_ISBLK(buf.st_mode)){
				out_dev(buf.st_rdev);
			}
			out_dev(buf.st_dev);
		}
	}
	return 0;
}
