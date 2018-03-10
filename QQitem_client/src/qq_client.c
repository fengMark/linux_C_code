#include<netdb.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>
#include<unistd.h>
#include<arpa/inet.h>
#include"usr_data.h"
#include"client_msg.h"
typedef struct{
	char usr_name[20];
	char password[20];
}Login_Data;

struct m{
	int sockfd;
	pthread_mutex_t f_lock;
}Sock;


char *promt_true = "\t发送成功\n";
cahr *promt_false = "\t发送失败\n";
void *write_th(void *arg);
void *read_th(void *arg);
void Talking_Friend(Friend friend);
int main(int argc,char *argv[]){
	char *serveraddr;
	cahr *port;
	Sock.sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0){
		perror("socket error");
	}
	struct sockaddr_in serveraddr;
	memset(&serveraddr,0,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET,argv[1],&serveraddr.sin_addr.s_addr);


	if(connect(Sock.sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr))<0){
		perror("connect error");
		exit(1);
	}


	Login_Data login;
	size_t size;
	int login_state;
	char *prompt = "please input login name and login password:>";
	while(1){
		memset(login,0,sizeof(login));
		write(STDOUT_FILENO,prompt,sizeof(prompt));
		size = read(STDIN_FILENO,login.usr_name,sizeof(login.usr_name));
		if(size<0) continue;
		size = read(STDIN_FILENO,login.password,sizeof(login.password));
		if(size<0) continue;
		if(write(Sock.sockfd,buff,sizeof(buff))<0){
			perror("write msg error");
			continue;
		}else{
			if(read(Sock.sockfd,&login_state,sizeof(logins_tate))<0){
				perror("read msg error");
				continue;
			}else{
				printf("%s\n",login_state==1 ?"login sucess":"login failed");
				if(login_state==1){//登录成功
					break;
				}
			}
		}
	
	}
	Friend_list * list = Create_list();
	Friend friend;
	int choice;
	while(1){
		while(1){
			if(read(Sock.sockfd,&friend,sizeof(friend))<0){
				perror("read friend error");
				break;
			}else{
				Add_Friend(list,friend);
			}
		}
		Print_list(list);
		scanf("%d",&choice);
		char ip[16];
		int port;
		struct sockaddr_in addr;
		memset(ip,0,sizeof(ip));
		read(STDIN_FILENO,ip,sizeof(ip));
		read(STDIN_FILENO,port,sizeof(port));
		inet_pton(AF_INET,ip,&addr.sin_addr);
		addr.sin_port = htons(port);
		Friend friend;
		friend.friend_ipaddr = addr;
		switch(choice){
			case 1://增加
				{
					Add_Friend(list,friend);
					break;	
				}
			case 2://删除
				{	
					Delete_Friend(list,friend);
					break;
				}
			case 3://通信
				{	
					
					Talking_Friend(friend);
					break;
				}
			case 4://退出
					Destroy_Friend(list);
					exit(1);
		}		
		
	}	
	close(Sock.sockfd);
	return 0;
}




void Talking_Friend(Friend friend){
	struct sockaddr addr_in = friend->friend_ipaddr;
	//根据对端的ip地址和端口号进信UDP打洞
	pthread_t readser;
	pthread_t writeser;
	pthread_mutex_init(&Sock.mutex,NULL);

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_create(&readser,&attr,read_th,(void *)addr);
	pthread_create(&writeser,&attr,write_th,(void *)addr);
	pthread_attr_destroy(&attr);
}
void *write_th(void *arg){//对指定的地址建立UDP连接，通信
	struct sockaddr_in addr= (struct sockaddr_in *)arg;
	Data data;
	data.addr = addr;
	read_msg(STDOIN_FILENO,&data.buff,sizeof(data.buff));
	pthread_mutex_lock(&Sock.mutex,NULL);
	int size = write_msg(Sock.sockfd,&data,sizeof(Data));
	pthread_mutex_unlock(&Sock.mutex);
	if(size<0){
		write_msg(STDOUT_FILENO,promt_false,sizeof(promt_false));
	}else if(size==0){
		write_msg(STDOUT_FILENO,promt_false;sizeof(promt_false));
		perror("服务器关闭");
		pthread_exit(0);
	}else{
		write_msg(STDOUT_FILENO,promt_true,sizeof(promt_true));
	}
}
void *read_th(void *arg){//接收所有的UDP数据包
	struct sockaddr_in addr = (struct sockaddr_in *)arg;
	Data data;
	data.addr = addr;
	char buff[512];
	int size;
	char ip[16];
	int port;
	pthread_mutex_lock(&Sock.mutex,NULL);
	size = read_msg(Sock.sockfd,&data,sizeof(Data));
	pthread_mutex_unlock(&Sock.mutex);
	if(size<0){
		perror("读取错误");
	}else if(size==0){
		pthread_exit(0);	
	}else{
		memset(ip,0,sizeof(ip));
		inet_ntop(AF_INET,&data.addr.sin_addr,ip,sizeof(ip));
		port = ntohs(data.addr.sin_port);
		printf("%s(%d)\n",ip,port);
		write_msg(STDOUT_FILENO,data.buff,sizeof(data.buff));
	}
}
