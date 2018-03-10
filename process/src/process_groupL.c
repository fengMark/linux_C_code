#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
int main(void){
	setpgid(getpid(),getpid());
	pid_t group1 = getpgid(getpid());
	int i =0;
	pid_t pid;
	pid_t group2;
	for(;i<2;i++){
		pid = fork();
		if(pid<0){
			perror("fork error");
		}else if(pid>0){
			if(i==0){
				setpgid(pid,pid);
			}
			if(i==1){
				setpgid(pid,group1);
			}
			break;//進程連中，父進程操作完成推出循環	
		}else{
			if(i==0){
				setpgid(getpid(),getpid());//子進程作爲組長進程
			}
			if(i==1){
				setpgid(getpid(),group1);
			}
		}
	}
	printf("pid:%d,ppid:%d,pgid:%d\n",getpid(),getppid(),getpgid(getpid()));
	for(i=0;i<2;i++){
		wait(0);
	}

	return 0;
}
