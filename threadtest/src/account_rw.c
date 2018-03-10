#include<pthread.h>
#include<assert.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"account_rw.h"
Account* create_account(int code,double balance){
	Account *a = (Account *)malloc(sizeof(Account));
	a->code = code;
	a->balance = balance;
	pthread_rwlock_init(&a->rwlock,NULL);
	return a;
}
double withdraw(Account *a,double amt){
	assert(a!=NULL);
	pthread_rwlock_wrlock(&a->rwlock);
	if(amt<0||amt>a->balance){
	pthread_rwlock_unlock(&a->rwlock);
		return 0.0;
	}
	double balance = a->balance;
	balance-=amt;
	a->balance = balance;
	pthread_rwlock_unlock(&a->rwlock);
	return amt;
}
double deposit(Account *a,double amt){
	assert(a!=NULL);
	pthread_rwlock_wrlock(&a->rwlock);
	if(amt<0){
		pthread_rwlock_unlock(&a->rwlock);
		return 0.0;
	}
	double balance = a->balance;
	balance +=amt;
	a->balance = balance;
	pthread_rwlock_unlock(&a->rwlock);
	return amt;
}
double get_balance(Account *a){
	assert(a!=NULL);
	pthread_rwlock_rdlock(&a->rwlock);
	double balance = a->balance;
	pthread_rwlock_unlock(&a->rwlock);
	return balance;
}
void destroy_account(Account *a){
	assert(a!=NULL);
	pthread_rwlock_destroy(&a->rwlock);
	free(a);
}


