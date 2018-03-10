#ifndef __ACCOUNT_SEM_H_
#define __ACCOUNT_SEM_H_
#include<semaphore.h>
typedef struct{
	int code;
	double balance;
	sem_t sem;
}Account;

extern Account* create_account(int code,double balance);
extern double withdraw(Account *a,double amt);
extern double deposit(Account *a,double amt);
extern double get_balance(Account *a);
extern void destroy_account(Account *a);


#endif

