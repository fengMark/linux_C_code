#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/wait.h>

char *cmd1 = "date > file1.txt";
char *cmd2 = "date > file2.txt";
void my_system(char *cmd);
int main(void){
  system("clear");
  system(cmd1);
  my_system(cmd2);
  return 0;
}
void my_system(char *cmd){
  pid_t pid;
  pid = fork();
  if(pid<0){
  perror("fork error\n");
  exit(1);
  }else if(pid==0){
  if(execlp("/bin/bash","/bin/bash","-c",cmd,NULL)==-1){
    perror("execlp error\n");
    exit(1);
   }
   wait(NULL);
  }
}
