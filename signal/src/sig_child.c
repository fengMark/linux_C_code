#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

void sig_handler(int signo){

	printf("child process deaded ,signo:%d\n",signo);
	//當父進程鋪貨到sigchld信號後要條用wait函數來回收子進程
	wait(0);//避免僵屍進程
}
void out(int n){
	int i;
	for(i=0;i<n;i++){
		printf("%d out %d\n",getpid(),i);
		sleep(2);
	}
}
int main(void)
{
	if(signal(SIGCHLD,sig_handler)==SIG_ERR){
		perror("signal sigchld error");
	}
	pid_t pid = fork();
	if(pid<0){
		perror("fork error");
		exit(1);
	}else if(pid>0){
		out(100);
	}else{
		out(10);
	}
	return 0;
}
