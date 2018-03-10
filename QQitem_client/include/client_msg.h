#ifndef __MSG_H_
#define __MSG_H_
#include<sys/types.h>
#include<sys/socket.h>
typedef struct{
	struct sockaddr_in *ip_addr;
	char buff[512];
}Data;
typedef struct {
	char head[20];//头部
	char checknum;//校验码
	Data data;
}Msg;

extern int write_msg(int sockfd,Data *buff,size_t len);

extern int read_msg(int sockfd,Data *buff,size_t len);

#endif
