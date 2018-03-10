#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<memory.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<math.h>
#include"calculator.h"
void invert_num(char *num){
	char ch;
	int i;
	int len = strlen(num);
	for(i=0;i<len/2;i++){
		ch=num[i];
		num[i] = num[len-i-1];
		num[len-i-1] = ch;
	}
	
}
Number*  create_num(char *num){
	Number *n = (Number*)calloc(1,sizeof(Number));
	if(n==NULL){
		perror("malloc error");
		exit(1);
	}
	if(num[0]=='-'){
		invert_num(num+1);
		n->sign = 1;
		n->len = strlen(num)-1;
		n->num = (char *)malloc(sizeof(char)*(n->len+1));
		if(n->num==NULL){
			perror("malloc error");
		}
		memcpy(n->num,num+1,n->len);
		n->num[n->len]='\0';
	}else{
		invert_num(num);
		n->sign = 0;
		n->len = strlen(num);
		n->num = (char *)malloc(sizeof(char)*(n->len+1));
		if(n->num==NULL){
			perror("malloc error");
		}
		memcpy(n->num,num,n->len);
		n->num[n->len]='\0';
	}
	return n;
}
void 	destroy_num(Number *num){
	assert(num!=NULL);
	free(num->num);
	num->num=NULL;
	free(num);
	num=NULL;
}
static char add(char a,char b,char *c){
	char  sum = (a-'0')+(b-'0')+((*c)-'0');
	*c = sum/10 +'0';
	return sum%10 +'0';
}
static char dec(char a,char b,char *c){
	char x = *c;
	if(a>b){
		*c = '0';
	}else if(a<b){
		*c = '1';
	}
	else{
		if(*c=='1'){
			*c='1';	
		}else{
			*c='0';
		}
	}	
	char res = ((a-'0'-(x-'0'))+10*((*c)-'0'))-(b-'0');
	return res+'0';
}
static Number* init_num(int sign,int len){
	Number *n = (Number *)malloc(sizeof(Number));
	assert(n!=NULL);
	n->sign = sign;
	n->len = len;
	n->num = (char *)malloc(sizeof(char)*(len+1));
	n->num[len] = '\0';
	return n;
}
Number* add_num(Number *num1,Number *num2){
	assert(num1!=NULL);
	assert(num2!=NULL);
	char c='0';
	int len;
	Number *sum,*c_sum,*sum_temp;
	int i=0;
	if(strlen(num1->num)>strlen(num2->num))	len=strlen(num1->num);
	else len = strlen(num2->num);
	if(num1->sign==num2->sign){//同号相加
		sum_temp = init_num(num1->sign,len);//
		while(num1->num[i]!='\0'&&num2->num[i]!='\0'){
			sum_temp->num[i] = add(num1->num[i],num2->num[i],&c);
			i++;
		}	
		if(num1->num[i]!='\0'){
			while(num1->num[i]!='\0'){
				sum_temp->num[i]=add(num1->num[i],'0',&c);
				i++;
			}
			//判断num1已经没有值了，且还有进位	
		}
		if(num2->num[i]!='\0'){
			while(num2->num[i]!='\0'){
				sum_temp->num[i]=add('0',num2->num[i],&c);
				i++;
			}		
		}
		if(c=='1'){
			sum =init_num(num1->sign,len+1);
			memcpy(sum->num,sum_temp->num,len);
			sum->num[len] = c;
		}else{	
			sum = init_num(num1->sign,len);
			memcpy(sum->num,sum_temp->num,len);
		}
	}
	else{
		if(num1->sign==1){
			num1->sign=0;
			sum = dec_num(num2,num1);
		}
		if(num2->sign==1){
			num2->sign=0;
			sum = dec_num(num1,num2);
		}
	}
	destroy_num(sum_temp);
	return sum;
}

static int compare(Number *num1,Number *num2){//比较大数字的绝对值大小
	if(num1->len>num2->len){
		return 1;
	}
	if(num1->len<num2->len){
		return 0;
	}
	if(num1->len==num2->len){
		int i = num1->len-1;
		for(;i>=0;i--){
			if(num1->num[i]>num2->num[i]){
				return 1;
			} 
			if(num1->num[i]<num2->num[i]){
				return 0;
			}
			if(num1->num[i]==num2->num[i]){
				continue;
			}
			
		}
		return -1;
	}
}
Number* dec_num(Number *num1,Number *num2){
	assert(num1!=NULL);
	assert(num2!=NULL);
	int i = 0;
	char c = '0';
	int len;
	Number *res;
	Number *res_temp;
	if(num1->len>num2->len) len = num1->len;
	else len = num2->len;
	if(num1->sign==num2->sign){
		int cpr = compare(num1,num2);
		if(cpr==-1){
			res = init_num(0,1);
			res->num[0] = '0';	
		}
		if(cpr==1){
			res_temp = init_num(num1->sign,num1->len);
			while(num1->num[i]!='\0'&&num2->num[i]!='\0'){
				res_temp->num[i]=dec(num1->num[i],num2->num[i],&c);
				i++;
			}
			if(num1->num[i]!='\0'){
				while(num1->num[i]!='\0'){
					res_temp->num[i] = dec(num1->num[i],'0',&c);
					i++;
				}
			}		
			for(i=num1->len-1;i>=0;i--){
				if(res_temp->num[i]!='0'){
					break;
				}
			}
			res = init_num(num1->sign,i);
			memcpy(res->num,res_temp->num,i+1);
			destroy_num(res_temp);
		}
		if(cpr==0){
			res_temp = init_num(1,num2->len);
			while(num1->num[i]!='\0'&&num2->num[i]!='\0'){
				res_temp->num[i]=dec(num2->num[i],num1->num[i],&c);
				i++;
			}
			if(num2->num[i]!='\0'){
				while(num2->num[i]!='\0'){
					res_temp->num[i]=dec(num2->num[i],'0',&c);
					i++;
				}
			}
			if(num1->sign==1){
				res_temp->sign = 0;
			}
			for(i=num2->len-1;i>=0;i--){
				if(res_temp->num[i]!='0'){
					break;
				}
			}
			res = init_num(num2->sign,i);
			memcpy(res->num,res_temp->num,i+1);
			destroy_num(res_temp);
		}
		res->len = strlen(res->num);
		return res;
	}else{
		if(num1->sign==1){
			num1->sign=0;
			res = add_num(num1,num2);
			res->sign = 1;
		}else{
			num2->sign=0;
			res = add_num(num1,num2);
			res->sign = 0;
		}
	}
	res->len = strlen(res->num);
	return res;
}

static char mul(char a,char b,char *c){
	char x = *c;
	char res = (((a-'0')*(b-'0'))+(x-'0'));
	*c = res/10+'0';
//	printf("%c    %c\n",*c,res%10+'0');
	return res%10+'0';
}
Number* mul_num(Number *num1,Number *num2){
	assert(num1!=NULL);
	assert(num2!=NULL);
	int i = 0;
	int k;
	char c = '0';
	Number *res,*temp,*res_temp;
	int len = num1->len+num2->len;
	if((num1->len==1&&num1->num[0]=='0')||(num2->len==1&&num2->num[0]=='0'))	{	
		res=init_num(0,1);
		res->num[0]='0';
		return res;
	}
	if(num1->sign==num2->sign){
		res_temp = init_num(0,len);
		temp=init_num(0,len);
	}else{
		res_temp = init_num(1,len);
		temp=init_num(1,len);
	}
	memset(res_temp->num,'0',len);
	for(k=0;k<num2->len;k++){
		memset(temp->num,'0',len);
		for(i=0;i<num1->len;i++){
			temp->num[k+i] = mul(num1->num[i],num2->num[k],&c);			}
		if(c!='0'){
			temp->num[k+i] = c;
			c='0';
		}
		res_temp=add_num(temp,res_temp);
	}
	for(i=len-1;i>=0;i--){
		if(res_temp->num[i]!='0'){
			break;
		}
	}
	res = init_num(1,i+1);
	memcpy(res->num,res_temp->num,i+1);
	res->sign = res_temp->sign;
	destroy_num(temp);
	destroy_num(res_temp);
	return res;
}
Number* div_num(Number *num1,Number *num2){
	assert(num1!=NULL);
	assert(num2!=NULL);
	if(num2->len==1&&num2->num[0]=='0'){
		fprintf(stderr,"input argument error:%s can`t became divnum\n",num2->num);
		return NULL;
	}
	Number *res;
	Number *res_bit;	
	if(num1->len==1&&num2->num[0]=='0'){
		res = init_num(0,1);
		res->num[0] = '0';
		return res;
	}
	int len = abs(num1->len-num2->len)+1+5;//设定商的结果的空间大小
	res = init_num(0,len);
	memset(res->num,'0',len);
	res_bit = init_num(0,1);//每次除除数的的商的一位
	Number *temp;
	Number *dec_temp,*dec_ctemp;
	Number *num1_temp;
	char i;
	int k,j;
	int x;
	int y;
	int cpr_n;
	int cpr_dec;
	if(num1->len<num2->len){//直接结果为小数：0.xxxxx
		k=2;
		res->num[0]='0';
		res->num[1]='.';
	while(k<len){
		for(i='0';i<='9';i++){
			res_bit->num[0]=i;
			temp = mul_num(res_bit,num2);
			num1_temp = init_num(0,temp->len);
	//		memcpy(num1_temp);	
			cpr_n = compare(temp,num1);
			if(cpr_n==1){
				res->num[k] = res_bit->num[0]-1;
				k++;
				break;
			}
			if(cpr_n==0){
				dec_temp = dec_num(num1,temp);
				cpr_dec = compare(dec_temp,temp);
				if(cpr_dec==1){
					continue;
				}else{
					num1 = init_num(0,dec_temp->len+1);
					num1->num[0]='0';
					while(dec_temp->num[j]!='\0'){
						num1->num[j+1] = dec_temp->num[j];
					}
					res->num[k] = res_bit->num[0];
					k++;
				}
			}
			if(cpr_n==-1){
				res->num[k] = res_bit->num[0];
				k++;
				break;
			}
		}
		}		
	}
	else{//直接结果为：yyyyyy.xxxxxxx
	    k=0;
	    num1_temp = init_num(0,num2->len);
	    for(x=num2->len-1,j=1;x>=0;x--,j++){
	          num1_temp->num[x] = num1->num[num1->len-j];
	    }
	   printf("%d\n",j);
	   printf("num1_temp:%s\n",num1_temp->num);
	   while(k<len){
		for(i='0';i<='9';i++){
		  res_bit->num[0]=i;
		  temp = mul_num(res_bit,num2);
		  cpr_n = compare(temp,num1_temp);
		printf("%d\n",cpr_n);
		if(cpr_n==1){
			dec_ctemp = dec_num(temp,num1_temp);		
			destroy_num(num1_temp);
			printf("j:%d\tres_bit->num-1:%c",j,res_bit->num[0]-1);
			num1_temp = init_num(0,dec_ctemp->len+1);
			if(j<=num1->len){
			num1_temp->num[0]=num1->num[num1->len-j];
			j++;
			}else{
			num1_temp->num[0]='0';
			}
			printf("%c\n",num1_temp->num[0]);
			memcpy(&num1_temp->num[0]+1,dec_ctemp->num,dec_ctemp->len);	
			printf("num1_temp:%s\n",num1_temp->num);
			destroy_num(dec_ctemp);
			destroy_num(temp);
			if((k-1)==num2->len){
				res->num[k]='.';
				k++;
			}
			res->num[k] = res_bit->num[0]-1;
			k++;
		 	break;	
		  }
		if(cpr_n==0){	
		        dec_temp = dec_num(num1_temp,temp);
			printf("dec_temp:%s\n",dec_temp->num);
			int comp = compare(dec_temp,num2);		
			if(comp==1||comp==-1){
				destroy_num(dec_temp);
				destroy_num(temp);
				continue;
			}else{
				destroy_num(num1_temp);		
				num1_temp = init_num(0,dec_temp->len+1);
				printf("j:%d\n",j);
				if(j<=num1->len){
				num1_temp->num[0]=num1->num[num1->len-j];
				j++;
				}else{
					num1_temp->num[0]='0';	
				}
				
				printf("%c\t%d\n",num1_temp->num[0],dec_temp->len);
				memcpy(&num1_temp->num[0]+1,dec_temp->num,dec_temp->len);	
				printf("num1_temp0000:%s\n",num1_temp->num);
				destroy_num(dec_temp);
				destroy_num(temp);
				if(j==num2->len){
					res->num[k]='.';
					k++;
				}
				res->num[k]=res_bit->num[0];
				k++;
				break;
		       }
		}
		if(cpr_n==-1){
			destroy_num(num1_temp);
			num1_temp = init_num(0,1);
			printf("j:%d\tres_bit:%c\n",j,res_bit->num[0]);
			if(j<=num1->len){
			num1_temp->num[0]=num1->num[num1->len-j];
			j++;
			}else{		
			if(dec_temp->len==1&&dec_temp->num[0]=='0')					{
					return res;
			}
			num1_temp->num[0]='0';
			}	
			printf("num1_temp:%s\n",num1_temp->num);
			destroy_num(temp);
			if(j==num2->len){
				res->num[k]='.';
				k++;
			}
			res->num[k] = res_bit->num[0];
			k++;
			break;
		}
	}
	
	}		
	}
	return res;
}
