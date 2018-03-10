#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(void){
	setpgid(getpid(),getpid());
	int i = 0;
	pid_t pid;
	pid_t group1 = getpgid(getpid());
	pid_t group2;
	for(;i<3;i++){
		pid = fork();
		if(pid<0){
			perror("fork error");
			exit(1);
		}else if(pid>0){
			if(i==0){
				setpgid(pid,group1);
			}
			if(i==1){
				setpgid(pid,pid);
				group2 = getpgid(pid);
			}
			if(i==2){
				setpgid(pid,group2);		
			}
		}else{
			if(i==0){
				setpgid(getpid(),group1);
			}
			if(i==1){
				setpgid(getpid(),getpid());
				group2 = getpgid(getpid());
			}
			if(i==2){
				setpgid(getpid(),group2);
			}
			break;
		}

	}
	printf("pid:%d,ppid:%d,pgid:%d\n",getpid(),getppid(),getpgid(getpid()));
	pause();
	return 0;
}
