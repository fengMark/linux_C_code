#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
	printf("fdasfagadg");
	sleep(10);
//	fsync(1);//对指定的文件描述副清缓存
	sync();//


	sleep(10);
	return 0;
}
