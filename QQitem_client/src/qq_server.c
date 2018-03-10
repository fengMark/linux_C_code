#include<pthread.h>
#include<netdb.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>
#include<arpa/inet.h>
#include<signal.h>
#include<time.h>
//#include"msg.h"
//#include"vector_pollfd.h"
//#include"vector_fd.h"
//#include<errno.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/select.h>
#include<sys/epoll.h>
typedef struct{
        char usr_name[20];
        char password[20];
}Login_Data;
struct epoll_event ev,evs[1024];
int sockfd;
struct sockaddr_in clientaddr;
int confd;
socklen_t clientaddr_len = sizeof(clientaddr);
struct sockaddr_in serveraddr;
int epfd;


void sig_handler(int signo){
	if(signo==SIGINT){
		printf("server close\n");
		close(sockfd);
		exit(1);
	}
}
/*
fd对应与某个连接的客户端
和某一个连接的客户端进行双向通信

*/

void do_service(struct epoll_event ev){
	char buff[512];
	int fd = ev.data.fd;
	memset(buff,0,sizeof(buff));
	size_t size = read(fd,buff,sizeof(buff));
	char *buf = "client closed\n";
	if(size==0){
		printf("%s",buf);
//		write(STDOUT_FILENO,buf,sizeof(buf));
		epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,&ev);
		close(ev.data.fd);
	}else if(size>0){
		printf("%s\n",buff);
//		write(STDOUT_FILENO,buff,sizeof(buff));
		if(write(fd,buff,size)<0){
			if(errno==EPIPE){//判断对方客户端是否已经关掉，客户端关掉的话则会产生EPIPE信号
				epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,&ev);
				perror("write error");
				close(ev.data.fd);
			}
		}
		
	}
	
}
void setnoblock(int* fd){
	int value;
 	 fcntl(*fd,F_GETFD,&value);
	value |=O_NONBLOCK;
	 fcntl(*fd,F_SETFD,&value);
}
void out_addr(struct sockaddr_in *clientaddr){
	char ip[16];
	memset(ip,0,sizeof(ip));
	int port = ntohs(clientaddr->sin_port);
	inet_ntop(AF_INET,
		&clientaddr->sin_addr.s_addr,ip,sizeof(ip));
	printf("%s(%d) connected\n",ip,port);
}
void * th_fn(void *arg){
	int n;
	int i;
	size_t size;
	Login_Data Login
	while(1){
		n = epoll_wait(epfd,evs,1024,1000);
		for(i=0;i<n;i++){
			if(evs[i].data.fd==sockfd){//监听到一个客户端连接到服务器
			 confd = accept(sockfd,(struct sockaddr*)&clientaddr,
				&clientaddr_len);		
				if(confd<0){
					perror("accept error");
				}
				size = read(confd,&Login,sizeof(Login));
				if(size>0){//登录从数据库中查询用户记录是否有匹配
					
				}else if(size==0){//客户端关闭连接

				}else{//读取错误


				}
				out_addr(&clientaddr);
				setnoblock(&confd);
				ev.data.fd=confd;
				ev.events=EPOLLIN;
				epoll_ctl(epfd,EPOLL_CTL_ADD,confd,&ev);
			}else if(evs[i].events&EPOLLIN){
				do_service(evs[i]);//接收到相应客户端的发送的数据进行转发
				ev.data.fd = evs[i].data.fd;
				ev.events = EPOLLIN|EPOLLOUT|EPOLLET;
				epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
			}else if(ev[i].events&EPOLLOUT){
				do_service(evs[i]);//发送到相应客户端的数据
				ev.data.fd = evs[i].data.fd;
				ev.events =EPOLLIN|EPOLLOUT|EPOLLET;
				epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
			}
		}
	}
	return (void*)0;
}
int main(int argc,char *argv[]){
	if(argc<2){
		printf("usage:%s #port\n",argv[0]);
		exit(1);
	}
	if(signal(SIGINT,sig_handler)==SIG_ERR){
		perror("signal sigint error");
		exit(1);
	}
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("socket error");
		exit(1);
	}
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons((short)atoi(argv[1]));
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	if(bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
		perror("bind error");
		exit(1);
	}
	if(listen(sockfd,10)<0){
		perror("listen error");
		exit(1);
	}
	setnoblock(&sockfd);
	ev.data.fd=sockfd;
	ev.events=EPOLLIN;
	epfd = epoll_create(10000);
	epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);


	pthread_t th;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	int err;
	if((err=pthread_create(&th,&attr,th_fn,(void*)0))!=0){
		perror("pthread create error");
		exit(1);
	}
	pthread_attr_destroy(&attr);
	while(1){
		usleep(1000);
	}
	return 0;
}
