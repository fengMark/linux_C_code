#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include"mysql.h"
#include<string.h>
#include<errno.h>
int main(int argc,char *argv[]){
	MYSQL *conn_ptr;
	conn_ptr=mysql_init(NULL);
	if(!conn_ptr){
		perror("mysql init failed");
		exit(1);
	}
	conn_ptr=mysql_real_connect(conn_ptr,"localhost","root","63140528","foo",0,NULL,0);
	if(conn_ptr){
		printf("connection success\n");
	}
	else{
		printf("connection failed\n");
	}
	return 0;
}
