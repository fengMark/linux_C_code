#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

void my_setbuf(FILE *restrict fp,char *restrict buf);
int main(int argc,char *argv[]){
 FILE *fp;
 fp =fopen("hello.txt","rb+");
    char *buf = (char *)malloc(sizeof(char)*BUFSIZ);
     my_setbuf(fp,buf);
/*	if(fp){
       
      }*/
 return 0;
}
void my_setbuf(FILE *restrict fp,char *restrict buf){
    //判斷fp的緩衝，關閉還是打開
	if(fp->base==NULL){
	  if(fp->_flag==0||fp->_flag==1){
  		if(setvbuf(fp,buf,_IOLBF,BUFSIZ)!=0){
        		perror("setbuf error\n");
			exit(1);	
		}
	}else if(fp->_flag>2){
	 	if(setvbug(fp,buf,_IOFBF,BUFSIZ)!=0){
			perror("setbuf IOFBF error\n");
			exit(1);
		}
        }
	}else{
         if(setvbuf(fp,NULL,_IONBF,0)!=0){
	 	perror("setvbuf _IONBF error\n");
		exit(1)
	   }
	}
}
