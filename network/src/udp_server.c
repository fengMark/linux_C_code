#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<signal.h>
#include<time.h>
#include<sys/types.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include"u_msg.h"
int sockfd;
void sig_handler(int signo){//处理用户的CTRL +C的前台进程组中断
	if(signo==SIGINT){
		printf("server close\n");
		close(sockfd);
		exit(1);
	}
}
void out_addr(struct sockaddr_in *clientaddr){
	int port = ntohs(clientaddr->sin_port);
	char ip[16];
	memset(ip,0,sizeof(ip));
	inet_ntop(AF_INET,&clientaddr->sin_addr.s_addr,ip,sizeof(ip));
	printf("client :%s(%d)\n",ip,port);

}
void do_service(){//udpzhuanfashuju
	struct sockaddr_in clientaddr;
	socklen_t  len = sizeof(clientaddr);
//	char buffer[1024];
	Package p;
//	memset(buffer,0,sizeof(buffer));
	if(recvfrom(sockfd,&p,sizeof(p),0,
			(struct sockaddr*)&clientaddr,&len)<0){
		perror("recvfrom error");
		
	}else{
		out_addr(&clientaddr);
		struct sockaddr_in sockaddr = p.sockaddr;
		char *ptr = p.buffer;
//		printf("client send into:%s\n",buffer);
//		long int t = time(0);
//		char *ptr = ctime(&t);
		size_t size = strlen(ptr)*sizeof(char);
		if(sendto(sockfd,ptr,size,0,
			(struct sockaddr*)&sockaddr,len)<0){
			perror("sendto error");
		}
	}

}
int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage:%s port\n",argv[0]);
		exit(1);
	}
	if(signal(SIGINT,sig_handler)==SIG_ERR){
		perror("signal error");
		exit(1);
	}
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd<0){
		perror("socket error");
		exit(1);
	}
	int res;
	int opt=1;
	//防止服务器停止之后长时间无法绑定端口	
	if((res=setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt)))<0){
		perror("setsockopt error");
		exit(1);
	}
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port = htons(atoi(argv[1]));
	serveraddr.sin_addr.s_addr = INADDR_ANY;//本机上的所有ip
	if(bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
		perror("bind error");
		exit(1);
	}
	while(1){
		do_service();
	}
}
