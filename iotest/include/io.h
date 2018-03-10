#ifndef _IO_H_
#define _IO_H_
#include<sys/types.h>


extern void copy(int fd1,int fd2);

extern void set_fl(int fd,int flag);

extern void clr_fl(int fd,int flag);

extern int lock_reg(int fd,int cmd,short type,off_t offset,short whence,off_t length);
//共享读锁：一个进程上了读锁，其他进程也可以上读锁
//独占写锁：一个进程上了独占写锁，其他进程不能上读锁和写锁
//阻塞版本的共享读锁
#define READ_LOCKW(fd,offset,whence,length) \
	lock_reg(fd,F_SETLKW,F_RDLCK,offset,whence,length)
//非阻塞版本的共享读锁
#define READ_LOCK(fd,offset,whence,length) \
	lock_reg(fd,F_SETLK,F_RDLCK,offset,whence,length)

//阻塞版本的独占写锁
#define WRITE_LOCKW(fd,offset,whence,length) \
        lock_reg(fd,F_SETLKW,F_WRLCK,offset,whence,length)
//非阻塞版本的独占写锁
#define WRITE_LOCK(fd,offset,whence,length) \
        lock_reg(fd,F_SETLK,F_WRLCK,offset,whence,length)
//解锁
#define UNLOCK(fd,offset,whence,length) \
        lock_reg(fd,F_SETLK,F_UNLCK,offset,whence,length)


#endif
