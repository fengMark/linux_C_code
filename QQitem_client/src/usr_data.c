#include<assert.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<sys/socket.h>
#include<string.h>
#include<sys/socket.h>
#include"usr_data.h"
#include<arpa/inet.h>
Friend_list* Create_list(){//登录成功后创建好友列表
	Friend_list *list=(Friend_list*)malloc(sizeof(Friend_list));
	list->friend_num = 0;
	list->friend_list=(Friend *)malloc(sizeof(Friend));
	list->friend_list->next=NULL;
	return list;
}
void Destroy_list(Friend_list* list){//退出好友列表时，销毁好友列表
	assert(list!=NULL);
	assert(list->friend_list!=NULL);
	Friend *p,*temp;
	p = list->friend_list;
	while(p!=NULL){
		temp = p->next;
		free(p);
		p=temp;
	}
	free(list->friend_list);
	free(list);
}
void Print_list(Friend_list *list){
	assert(list!=NULL);
	char *prompt = "friend list is nothing\n";
	if(list->friend_num==0){
		 write(STDOUT_FILENO,prompt,sizeof(prompt));
		return;
	}
	char ip[16];
	int port;
	Friend *head = list->friend_list;
	while(head->next!=NULL){
		write(STDOUT_FILENO,head->next->usr,sizeof(head->next->usr));
		write(STDOUT_FILENO,"\t",1);
		memset(ip,0,sizeof(ip));
		inet_ntop(AF_INET,&head->friend_ipaddr->sin_addr,ip,sizeof(ip));//网络字节序转换成点分十进制
		port = ntohs(head->friend_ipaddr->sin_port);
		printf("\t %s(%d)\t %s\n",ip,port,head->flag==1 ? "在线":"下线");
	}
	printf("load complete\n");
}
void Add_Friend(Friend_list* list,Friend p){//添加好友
	assert(list!=NULL);
	Friend *head = list->friend_list;
	while(head!=NULL){
		if(!strcmp(head->usr,p.usr)){//判断用户是否存在，存在更新ip地址和状态
			head->flag = p.flag;
			head->friend_ipaddr = p.friend_ipaddr;
			return;
		}
		head=head->next;
	}
	head->next=&p;
	list->friend_num++;
}
void Delete_Friend(Friend_list* list,Friend p){//删除好友
	assert(list!=NULL);
	if(list->friend_num==0) return;
	else{
		Friend *head = list->friend_list;
		Friend *temp;
		while(head->next!=NULL){
			if(!strcmp(head->next->usr,p.usr)){
				temp = head->next;
				head->next = temp->next;
				free(temp->friend_ipaddr);
				free(temp);		
			}
			head=head->next;
		}
	}
}

