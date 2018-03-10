#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<memory.h>

int main(void){
	FILE *fp;
	fp = popen("cat /etc/passwd","r");
	char buf[512];
	memset(buf,0,sizeof(buf));
	while(fgets(buf,sizeof(buf),fp)!=NULL){
		printf("%s",buf);
	}
	pclose(fp);
//-----------------------------
	printf("\n-----------------------------\n");
	fp = popen("wc -l","w");
	fprintf(fp,"1\n2\n3\n");
	pclose(fp);
	return 0;
}
