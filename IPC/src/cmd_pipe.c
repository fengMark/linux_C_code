#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>

char *cmd1[3]={"/bin/cat","/etc/passwd",NULL};
char *cmd2[3] = {"/bin/grep","root",NULL};

void sig_handler(int signo){
	waitpid(-1,NULL,WNOHANG);
}
int main(void){
	if(signal(SIGCHLD,sig_handler)==SIG_ERR){
		perror("signal error");
		exit(1);
	}
	int fd[2];
	int i = 0;
	pid_t pid;
	if(pipe(fd)<0){
		perror("pipe error");
		exit(1);
	}
	for(;i<2;i++){
		pid = fork();
		if(pid<0){
			perror("fork error");
			exit(1);
		}else if(pid>0){
			if(i==1){
				close(fd[0]);
				close(fd[1]);
	//			wait(NULL);
	//			wait(NULL);
			}
		}
		else{
			if(i==0){
				close(fd[0]);
				if(dup2(fd[1],STDOUT_FILENO)!=STDOUT_FILENO){
						perror("dup2 error");
						exit(1);
				}
				close(fd[1]);
				if(execvp(cmd1[0],cmd1)<0){
					perror("execvp error");
					exit(1);
				}
				break;
			}
			if(i==1){
				close(fd[1]);
				if(dup2(fd[0],STDIN_FILENO)!=STDIN_FILENO){
						perror("dup2 error");
						exit(1);
				}
				close(fd[0]);
				if(execvp(cmd2[0],cmd2)<0){
					perror("execvp error");
					exit(1);
				}
				break;
			}	
		}
	}
	return 0;
}
