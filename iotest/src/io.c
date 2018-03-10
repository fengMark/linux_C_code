#include"io.h"
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

#define BUF_LEN 1024
void copy(int fd1,int fd2){
   char buf[BUF_LEN];
	ssize_t size;
   while((size = read(fd1,buf,BUF_LEN))!=-1){
	 if(write(fd2,buf,size)!=size){
 		perror("write error\n");
		exit(1);
             }
	}if(size<0){
	   fprintf(stderr,"read error:%s",strerror(errno));
		exit(1);
 	}
	exit(0);
}
void set_fl(int fd,int flag){
     int val = fcntl(fd,F_GETFL);//获取当前文件描述符的属性
	val |= flag;//或操作，设置文件属性的标志
	if(fcntl(fd,F_SETFL,val)<0){
	 perror("fcntl error");
	}
}
void clr_fl(int fd,int flag){
   	int val = fcntl(fd,F_GETFL);//获取当前文件描述符的属性
	val &= ~flag;//文件属性标志取反，与操作，清除标志位
	if(fcntl(fd,F_SETFL,val)<0){
	perror("fcntl error");
	}
}
int lock_reg(int fd,int cmd,short type,off_t offset,short whence,off_t length){
    struct flock flock;
	flock.l_type = type;//锁的类型
	flock.l_start = offset;//加锁和解锁的起始地址
	flock.l_whence = whence;//枷锁解锁的字节偏移量
	flock.l_len = length;//区域的字节长度
	if(fcntl(fd,cmd,&flock)<0){
	perror("fcntl error");
	return 0;
	}
 return 1;
}
