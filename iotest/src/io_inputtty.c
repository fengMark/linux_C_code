#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<stdio.h>
#include<linux/input.h>

int main(int argc,char *argv[]){
	int fd;
	struct input_event event;
	char name[256] = "Unknow name";
  	if((fd = open("/dev/input/event1",O_RDONLY))<0){
		perror("open error\n");
		exit(1);
	}
	if(ioctl(fd,EVIOCGNAME(sizeof(name)),name)==-1){
		printf("%s\n",name);
		exit(1);
	}
	while(1){
	if(read(fd,&event,sizeof(event))<0){
		perror("read error");
		exit(1);
	}
	if(EV_KEY==event.type){
		printf("input code:%d\n",event.code);
		if(event.code==16){
		break;
		}
	}
}
	
		
	close(fd);
	return 0;
}
