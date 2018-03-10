#ifndef __CALCULATOR_H_
#define __CALCULATOR_H_
typedef struct{
	int sign;
	int len;
	char *num;
}Number;
extern void invert_num(char *num);
extern Number*  create_num(char *num);
extern void 	destroy_num(Number *num);
extern Number* 	add_num(Number *num1,Number *num2);
extern Number* 	dec_num(Number *num1,Number *num2);
extern Number* 	mul_num(Number *num1,Number *num2);
extern Number* 	div_num(Number *num1,Number *num2);

#endif

