#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
void sig_handler(int signo){
	waitpid(-1,NULL,WNOHANG);
}
int main(void){
	if(signal(SIGCHLD,sig_handler)==SIG_ERR){
		perror("signal error");
		exit(1);
	}
	int fd[2];
	if(pipe(fd)<0){
	perror("pipe error");
	exit(1);
	}
	pid_t pid;
	pid = fork();
	if(pid<0){
		perror("fork error");
		exit(1);
	}else if(pid>0){
		close(fd[0]);
		int start = 1,end = 100;
		if(write(fd[1],&start,sizeof(int))!=sizeof(int)){
			perror("write error");
			exit(1);
		}
		
		if(write(fd[1],&end,sizeof(int))!=sizeof(int)){
			perror("write error");
			exit(1);
		}
		close(fd[1]);
		wait(NULL);
	}else{
		close(fd[1]);
		int start,end;
		if(read(fd[0],&start,sizeof(int))<0){
			perror("read error");
			exit(1);
		}
		
		if(read(fd[0],&end,sizeof(int))<0){
			perror("read error");
			exit(1);
		}
		printf("start:%d,end:%d\n",start,end);
		close(fd[0]);
		exit(1);
	}
	return 0;
}
