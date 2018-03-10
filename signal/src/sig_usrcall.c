#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

void sig_handler(int signo){
	printf("signal occured\n");
}
void usrcall(){
	printf("begin running usrcall\n");
	sleep(10);
	printf("end running usrcall\n");
}
int main(void){
	if(signal(SIGTSTP,sig_handler)==SIG_ERR){
		perror("signal error");
		exit(1);
	}

	printf("begin running main\n");
	usrcall();
	printf("end running main\n");
	return 0;
}
