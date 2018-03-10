#include<malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"account_sem.h"
Account* create_account(int code,double balance){
	Account *a = (Account *)malloc(sizeof(Account));
	a->code = code;
	a->balance = balance;
	sem_init(&a->sem,0,1);
	return a;
}
double withdraw(Account *a,double amt){
	assert(a!=NULL);
	sem_wait(&a->sem);
	if(amt<0||amt>a->balance){
		sem_post(&a->sem);
		return 0.0;
	}
	double balance = a->balance;
	balance -=amt;
	a->balance = balance;
	sem_post(&a->sem);
	return amt;
}
double deposit(Account *a,double amt){
	assert(a!=NULL);
	sem_wait(&a->sem);
	if(amt<0){
		sem_post(&a->sem);
		return 0.0;
	}
	double balance = a->balance;
	balance += amt;
	a->balance = balance;
	sem_post(&a->sem);
	return amt;
}
double get_balance(Account *a){
	assert(a!=NULL);
	sem_wait(&a->sem);
	double balance = a->balance;
	sem_post(&a->sem);
	return balance;
}
void  destroy_account(Account *a){
	assert(a!=NULL);
	sem_destroy(&a->sem);
	free(a);
}


