#include<unistd.h>
#include<stdio.h>
#include<string.h>

extern char **environ;

void show_env(){
	int i = 0;
	char *env;
	while((env = environ[i])){
		printf("%s\n",env);
		i++;
	}

}
int main(void){
	show_env();
	return 0;
}
/*int main(int argc,char *argv[],char **envp){
	char *env;
	int i= 0;
	while((env = envp[i])!=NULL){
		printf("%s\n",env);
		i++;
	}
	return 0;
}*/
