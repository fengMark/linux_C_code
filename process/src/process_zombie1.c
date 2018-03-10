#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<string.h>

int main(){

 pid_t pid;
 pid = fork();
 if(pid<0){
 perror("fork error\n");
 exit(1);
 }else if(pid==0){
 printf("pid :%d,ppid: %d\n",getpid(),getppid());
 exit(0);
 }

 wait(NULL);
/* while(1){
 sleep(1);
 }
*/
 exit(0);
}
