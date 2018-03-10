#include<signal.h>
#include<stdio.h>
#include<stdlib.h>


void sig_handler(int signo){

}
int main(void){
	if(signal(SIGUSR1,sig_handler)==SIG_ERR){

	}
	if(signal(SIGUSR2,sig_handler)==SIG_ERR){

	}
	sigset_t oset;
	sigemptyset(&oset);
	if((sigprocmask(SIG_BLOCK,NULL,&oset))<0){
		
	}
	return 0;
}
