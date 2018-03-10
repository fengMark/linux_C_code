#include<unistd.h>
#include<stdio.h>
#include<apue.h>
#include<stdlib.h>
static void my_exit1(void);
static void my_exit2(void);
int main(){
  
  if(atexit(my_exit1)!=0){
   printf("cant register  my_eixt1");
   }
  if(atexit(my_exit2)!=0){
   printf("cant register my_eixt2");
   }
   if(atexit(my_exit1)!=0){
   printf("cant register my_eixt1");
   }
   if(atexit(my_exit2)!=0){
   printf("cant register my_eixt2");
   }
  printf("main is done");
 return 0;
}
static void my_exit1(void){
  printf("my_eixt1  handler");
}
static void my_exit2(void){
  printf("my_eixt2  handler");
}
