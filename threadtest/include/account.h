#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_
#include<pthread.h>
typedef struct{
	int code;
	double balance;
	//定義一把互斥鎖，用來對多線程操作的銀行賬戶（共享資源）進行枷鎖保護	
	pthread_mutex_t mutex;
	//把鎖與共享資源進行綁定
	/*
	建議互斥鎖用來鎖定一個賬戶，和賬戶綁定在一起，盡量不舍值成全局變量
	，否則可能出現一把鎖去鎖幾百個賬戶，導致並發性能降低

	*/


}Account;

extern Account* create_account(int code,double balance);
extern void destroy_account(Account *a);
extern double withdraw(Account *a,double amt);
extern double deposit(Account *a,double amt);
extern double get_balance(Account *a);

#endif
