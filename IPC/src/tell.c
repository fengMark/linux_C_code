#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"tell.h"
#include<unistd.h>
//初始化管道
static int fd[2];
void init(){
	if(pipe(fd)<0){
		perror("pipe error");
		
	}
}
//利用管道進行等待
void wait_pipe(){
	char c;
	//默認讀寫是阻塞行的
	if(read(fd[0],&c,1)<0){
		perror("wait pipe error");
	}
}
//利用管道進行通知
void notify_pipe(){
	char c = 'c';
	if(write(fd[1],&c,1)!=1){
		perror("write pipe error");
	}
}
//銷毀管道
void destory_pipe(){
	close(fd[0]);
	close(fd[1]);
}
