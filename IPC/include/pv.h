#ifndef __PV_H_
#define __PV_H_
//初始化semnums個信號燈/信號量的值（value）
extern int I(int semnums,int value);
//對信號量集（semid）中的信號燈（semnum）做p(value)操作
extern void P(int semid,int senum,int value);
//對信號集（semid）中的信號燈（semnum）做v(value)操作
extern void V(int semid,int senum,int value);

extern void D(int semid);

#endif
