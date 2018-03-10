#ifndef __TELL_H_
#define __TELL_H_

//初始化管道
extern void init();
//利用管道進行等待
extern void wait_pipe();
//利用管道進行通知
extern void notify_pipe();
//銷毀管道
extern void destory_pipe();
#endif
