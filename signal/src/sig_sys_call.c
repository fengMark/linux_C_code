#include<signal.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

void sig_handler(int signo){
	printf("signal occured\n");

}
int main(void){
	if(signal(SIGTSTP,sig_handler)==SIG_ERR){
		perror("signal error");
		exit(1);
	}
	char buffer[256];
	printf("begin running main\n");
	read(STDIN_FILENO,buffer,sizeof(buffer));
	write(STDOUT_FILENO,buffer,sizeof(buffer));
	printf("end running main\n");
 	return 0;
}
