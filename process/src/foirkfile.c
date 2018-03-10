#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
int g_v=0;
int main()
{
  int s_v=0;
  static int a_v=0;
  pid_t pid;
  fprintf(stdout,"pid: %d\n",getpid());
  pid = fork();
  if(pid<0){
  fprintf(stderr,"fork error\n");
  }else if(pid>0){
   printf("I am parent process pid is %d,  ppid is %d ,fork return value is %d",getpid(),getppid(),pid);
   printf("g_v:%p,a_v:%p,s_v:%p\n",&g_v,&a_v,&s_v);
  }else if(pid==0){
   printf("I am child process pid is %d, ppid is %d,fork return value is %d\n",getpid(),getppid(),pid);
   printf("g_v:%p,a_v:%p,s_v:%p\n",&g_v,&a_v,&s_v);

  }
  printf("child and parent hhan:pid:%d\n",getpid());
  printf("g_v:%d.a_v:%d,s_v:%d\n",g_v,a_v,s_v);
  sleep(1);
 return 0;
}
