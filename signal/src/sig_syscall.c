#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
void sig_handler(int signo){
	sleep(10);
	printf("SIGTSTP occured\n");
	
}
int main(void){
	if(signal(SIGTSTP,sig_handler)==SIG_ERR){
		perror("signal error");
		exit(1);
	}
	printf("begin running main\n");
	pause();
	printf("end running main\n");
}
