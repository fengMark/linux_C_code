#include<signal.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
static int j = 0;
void sig_handler(int signo){
	if(signo==SIGALRM){
		printf("clock time out\n");		
		alarm(5);
		if(j==16){
			alarm(0);
		}
		j++;
	}
}
void out_data(void){
	int i = 1;
	while(i<=30){
		double d = drand48();
		printf("%-10d:%lf\n",i++,d);
/*		if(i==16){
			alarm(0);
		}*/
		sleep(1);
	}

}
int main(void){
	if(signal(SIGALRM,sig_handler)==SIG_ERR){
		perror("signal sigalrm error");
	}
	alarm(5);
	printf("begin running main\n");
	out_data();
	printf("end running main\n");
	return 0;
}
