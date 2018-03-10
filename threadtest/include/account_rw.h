#ifndef __ACCOUNTRW_H_
#define __ACCOUNTRW_H_
#include<pthread.h>
typedef struct{
	int code;
	double balance;
	pthread_rwlock_t rwlock;
}Account;

extern Account* create_account(int code,double balance);
extern double withdraw(Account *a,double amt);
extern double deposit(Account *a,double amt);
extern double get_balance(Account *a);
extern void destroy_account(Account *a);


#endif
