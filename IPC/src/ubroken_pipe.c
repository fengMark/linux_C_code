#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<string.h>

int main(void){
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
	}else if(pid==0){
		close(fd[0]);
		char *s ="1234";
		write(fd[1],s,sizeof(s));
		close(fd[1]);
	}else{
		close(fd[1]);
		sleep(5);
		char c;
		while(1){
			if(read(fd[0],&c,1)==0){
				printf("\n end of pipe\n");
				break;
			}
			else{
				printf("%c",c);
			}
		}
		close(fd[0]);
		wait(NULL);
	}

	return 0;
}
