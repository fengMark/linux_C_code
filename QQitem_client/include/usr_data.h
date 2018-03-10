#ifndef __USR_DATA_H_
#define __USR_DATA_H_
#include<sys/socket.h>
struct sockaddr_in;
struct Friend{
	char usr[20];
	char flag;
	struct sockaddr_in *friend_ipaddr;
	struct Friend *next;		
};
typedef struct Friend Friend;
typedef struct{
	int friend_num;
	Friend *friend_list;
}Friend_list;
extern Friend_list* Create_list();
extern void Destroy_list(Friend_list*);
extern void Print_list(Friend_list*);
extern void Add_Friend(Friend_list*,Friend);
extern void Delete_Friend(Friend_list*,Friend);



#endif
