#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>


int main(int argc,char *argv[]){
 pid_t pid;
 int counter;
 if(argc<2){
  counter = 2;
 }else{
  counter = atoi(argv[1]);
 }
 int i=1;
 for(;i<counter;i++){
  pid = fork();
 if(pid<0){
 perror("fork error\n");
 exit(1);
 }else if(pid>0)  break;
 }
 printf("pid:%d,ppid:%d\n",getpid(),getppid());
 while(1){
 sleep(2);
 }
 return 0;
}
