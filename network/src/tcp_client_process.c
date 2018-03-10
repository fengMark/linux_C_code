#include<netdb.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>
#include<unistd.h>
#include<arpa/inet.h>
#include"msg.h"
int main(int argc,char *argv[]){
	if(argc<3){
		fprintf(stderr,"usage:%s ip port\n",argv[0]);
		exit(1);
	}
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("socket error");
	}
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET,argv[1],&serveraddr.sin_addr.s_addr);


	if(connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
		perror("connect error");
		exit(1);
	}


	char buff[512];
	size_t size;
	char *prompt = ">";
	while(1){
		memset(buff,0,sizeof(buff));
		write(STDOUT_FILENO,prompt,1);
		size = read(STDIN_FILENO,buff,sizeof(buff));
		if(size<0) continue;
		buff[size-1]='\0';
		if(write_msg(sockfd,buff,sizeof(buff))<0){
			perror("write msg error");
			continue;
		}else{
			if(read_msg(sockfd,buff,sizeof(buff))<0){
				perror("read msg error");
				continue;
			}else{
				printf("%s\n",buff);
			}
		}
	
	}	
	close(sockfd);
	return 0;
}
