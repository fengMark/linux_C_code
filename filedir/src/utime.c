#include<unistd.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<utime.h>
struct stat get_stat(const char *pathname,struct stat buf){
 	if(lstat(pathname,&buf)<0){
		perror("lstat error");
		exit(1);
	}
	return buf;
}
void out(struct stat buf){
	printf("atime:%s",ctime(&buf.st_atime));
	printf("mtime:%s",ctime(&buf.st_mtime));
	printf("ctime:%s",ctime(&buf.st_ctime));
}
int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage %s file",argv[0]);
		exit(1);
	}
	struct stat buf;
	buf = get_stat(argv[1],buf);
	out(buf);
	printf("---------------------------------------\n");
	struct stat back = buf;
	utime(argv[1],NULL);
	buf = get_stat(argv[1],buf);
	out(buf);
	printf("---------------------------------------\n");
	struct utimbuf ubuf;
	ubuf.actime = back.st_atime;
	ubuf.modtime = back.st_mtime;
	utime(argv[1],&ubuf);
	buf = get_stat(argv[1],buf);
	out(buf);
	printf("---------------------------------------\n");
	return 0;
}
