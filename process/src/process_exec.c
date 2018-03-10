#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdio.h>

char *cmd1 = "cat";
char *cmd2 = "/bin/cat";
char *argv1 = "/etc/passwd";
char *argv2 = "/etc/group";

int main(void){
 pid_t pid;
 pid = fork();
 if(pid<0){
 perror("fork error\n");
 exit(1);
 }else if(pid==0){
  if(execl(cmd2,cmd2,argv1,argv2,NULL)==-1){//exec函數不帶p時候，第一個參數必須是絕對路徑
   perror("exec error\n");
   exit(1);
 }
 wait(NULL);
 }
 return 0;
}
