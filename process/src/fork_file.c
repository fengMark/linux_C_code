#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[]){
 if(argc<2){
 perror("argument error\n");
 exit(1);
 }
 int  fd;
 fd = open(argv[1],O_WRONLY);
 if(fd<2){
 perror("open file error\n");
 exit(1);
 }
 pid_t pid;
 pid = fork();
 if(pid<0){
 perror("fork error\n");
 exit(1);
 }else if(pid>0){
 if(lseek(fd,0L,SEEK_END)<0){
 perror("lseek error\n");
 }
 }else{
 char *str = "hello linux go learning\n";
 size_t size = strlen(str) + sizeof(char);
 sleep(3);
 if(write(fd,str,size)==-1){  //fd是從父進程中繼承而來的
 perror("write error\n");
 exit(0);
 }

 close(fd);
 sleep(1);
 }
 return 0;
}
