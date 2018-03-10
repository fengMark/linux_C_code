#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>
void pre_status(int status);
int main(){
pid_t pid;
int status;
  pid = fork();
  if(pid<0){
   perror("fork error");
   exit(1);
  }else if(pid==0){
   printf("pid : %d,ppid :%d\n",getpid(),getppid());
   exit(3);
  }
  wait(&status);
  pre_status(status);
  pid = fork();
  if(pid<0){
   perror("fork error");
   exit(1);
  }else if(pid==0){
   int i=10,j; 
   printf("pid : %d,ppid :%d\n",getpid(),getppid());
   i /=0;
  }
  wait(&status);
  pre_status(status);


  pid = fork();
  if(pid<0){
   perror("fork error");
   exit(1);
  }else if(pid==0){
   printf("pid : %d,ppid :%d\n",getpid(),getppid());
   pause();
  }
  int i=0;
  do{
  pid =  waitpid(pid,&status,WNOHANG|WUNTRACED);
  if(pid==0) sleep(1);
  }while(pid==0);
  pre_status(status);
}
void pre_status(int status){
    if(WIFEXITED(status)){
     printf("normal status:%d\n",WEXITSTATUS(status));
    }else if(WIFSIGNALED(status)){
     printf("signal status:%d\n",WTERMSIG(status));
    }else if(WIFSTOPPED(status)){
     printf("stop status:%d\n",WSTOPSIG(status));
     }
}
