#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

void sig_handler(int signo){

	printf("%d,%d occured\n",getpid(),signo);
}
int main(void){

	if(signal(SIGTSTP,sig_handler)==SIG_ERR){
		perror("signal sigtstp error");
	}
	
	if(signal(SIGINT,sig_handler)==SIG_ERR){
		perror("signal sigint error");
	}
	int i = 0;
	while(i<30){
		printf("%d out %d \n",getpid(),i++);
		sleep(1);
	}
	return 0;
}
