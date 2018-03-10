#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
char *cmd1 = "cat";
char *cmd2 = "/bin/cat";
char *argv1 = "/etc/passwd";
char *argv2 = "/etc/group";
int main(void){
 pid_t pid;
 int status;
 pid = fork();
 if(pid<0){
 perror("fork error\n");
 exit(1);
 }else if(pid==0){
  char *argv[4] = {cmd1,argv1,argv2,NULL};
  if((execvp(cmd2,argv))==-1){
  perror("execvp error\n");
  exit(1);
  }
 }
 do{
   pid = waitpid(pid,&status,WNOHANG);
   if(pid==0)  sleep(1);
}while(pid==0);
 return 0;
}
