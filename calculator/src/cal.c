#include<unistd.h>
#include"calculator.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	if(argc<3){
		fprintf(stderr,"usage:%s num1 num2\n",argv[0]);
		exit(1);
	}
	Number *num1 = create_num(argv[1]);
	Number *num2 = create_num(argv[2]);
//	Number *sum = add_num(num1,num2);
//	printf("result:%c %s  \n",(sum->sign==1 ? '-':'+'),sum->num);
//	Number *dec = dec_num(num1,num2);
//	printf("dec result:%c %s \n",(dec->sign==1 ? '-': '+'),dec->num);
//	Number *mul = mul_num(num1,num2);
//	printf("mul result:%c %s \n",(mul->sign==1 ? '-': '+'),mul->num);
	Number *div = div_num(num1,num2);
	printf("div result:%c %s \n",(div->sign==1 ? '-': '+'),div->num);
	destroy_num(num1);
	destroy_num(num2);
	destroy_num(div);
//	destroy_num(mul);
	return  0;
}
