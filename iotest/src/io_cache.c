#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main(void){
//	printf("hello cache");//行緩存沒有遇到換行父
	printf("hello cache");
/*	while(1){
	sleep(1);
   	}*/
 _exit(0);//該函數調用不會衝洗緩存
//	return 0;
}
