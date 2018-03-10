#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main(void){
	int fda[2],fdb[2];
	
	if((pipe(fda)<0)||(pipe(fdb)<0)){
		perror("pipe error");
		exit(1);
	}
	pid_t pid;
	pid = fork();
	if(pid<0){
		perror("fork error");
		exit(1);
	}else if(pid==0){
		close(fda[1]);
		close(fdb[0]);
		if(dup2(fda[0],STDIN_FILENO!=STDIN_FILENO)){
			perror("dup2 error");
		}
		if(dup2(fdb[1],STDOUT_FILENO!=STDOUT_FILENO)){
			perror("dup2 error");
		}
		close(fda[0]);
		close(fdb[1]);
		if(execlp("bin/add","bin/add",NULL)<0){
			perror("exec error");
			exit(1);
		}
	}else{
		close(fda[0]);
		close(fdb[1]);
		int x,y;
		printf("please input x and y:");
		scanf("%d %d",&x,&y);
		if(write(fda[1],&x,sizeof(int))!=sizeof(int)){
			perror("write error");
		}
		if(write(fda[1],&y,sizeof(int))!=sizeof(int)){
			perror("write error");
		}
		int result=0;
		if(read(fdb[0],&result,sizeof(int))!=sizeof(int)){
			perror("read error");
		}else{
			printf("result is %d\n",result);
		}
		close(fda[1]);
		close(fdb[0]);
		wait(NULL);
		
	}
	exit(1);
}
