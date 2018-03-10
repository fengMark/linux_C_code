#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<malloc.h>
typedef struct{
	int fd[];
	int semid;
}Pipe;
Pipe * create_pipe(int *fd){
	Pipe *p = (Pipe *)calloc(1,sizeof(Pipe));
	if(p==NULL){
		perror("calloc error");
		exit(1);
	}
	p->fd = (int *)calloc(1,sizeof(int));
	p->fd[0] =fd[0];
	p->fd[1] =fd[1];
	p->semid = I(2,1);
}
void write_pipe(Pipe *p,int val){
	//write
	write(p->fd[1],&val,sizeof(val));
	V(p->semid,0,1);
	//v(1)
	P(p->semid,1,1);
	//p(2)
}
void read_pipe(Pipe *p){
	//P(1)
	P(p->semid,0,1);	
	//read
	int re;
	read(p->fd[0],&re,sizeof(int));
	printf("pid :%d read :%d from pipe\n",getpid(),re);
	//v(2)
	V(p->semid,1,1);
}
void destory_pipe(Pipe *p){
	assert(p!=NULL);
	free(p->fd);
	free(p);
}
void sig_handler(int signo){
	waitpid(-1,NULL,WNOHANG);
}
int main(void){
	if(signal(SIGCHLD,sig_handler)==SIG_ERR){
		perror("signal error");
		exit(1);
	}	
	int fda[2];
	int fdb[2];
	
	if(pipe(fda)<0){
		perror("pipe error");
		exit(1);
	}
	if(pipe(fdb)<0){
		perror("pipe error");
		exit(1);
	}
	int i=0;
	pid_t pid;
	for(;i<2;i++){
		pid = fork();
		if(pid<0){
			perror("fork error");
			exit(1);
		}else if(pid==0){
			if(i==0){
				close(fda[0]);
				close(fdb[1]);
				int fd[] = {fdb[0],fda[1]};
				Pipe *p = creat_pipe(fd);
				int i=100;
				while(i--){
					write_pipe(p,i);
				}
				break;
			}
			if(i==1){
				close(fda[1]);
				close(fdb[0]);
				
				int fd[] ={fda[0],fdb[1]};
				Pipe *p = creat_pipe(fd);
				break;
			}
		}else{

			close(fda[0]);
			close(fdb[0]);
			close(fda[1]);
			close(fdb[1]);
		}
	}

}
