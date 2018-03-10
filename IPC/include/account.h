#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_


typedef struct{
	int code;
	double balance;
	int semid;//在共享資源上綁定一個信號量集
}Account;

extern double withdraw(Account *a,double amt);
extern double deposit(Account *a,double ammt);
extern double get_balance(Account *a);


#endif
