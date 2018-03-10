#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/types.h>
#include<stdio.h>
int main(int argc,char *argv[]){
	if(argc<2){
	fprintf(stderr,"usage:%s files",argv[0]);
	exit(1);
	}
	int i;
	for(i=1;i<argc;i++){
	 	 if(access(argv[i],F_OK)){
 			fprintf(stderr,"%s files is not exesit",argv[i]);
			continue;
		   }
		else{
		        if(access(argv[i],R_OK)){
				fprintf(stderr,"%d can`t read\n",getpid());
			}else{
				printf("%d can read\n",getpid());
			}		
		   
		        if(access(argv[i],W_OK)){
				fprintf(stderr,"%d can`t write\n",getpid());
			}else{
				printf("%d can write\n",getpid());
			}
					
		        if(access(argv[i],X_OK)){
				fprintf(stderr,"%d can`t execute\n",getpid());
			}else{
				printf("%d can execute\n",getpid());
			}		
		    }
	}
	return 0;
}
