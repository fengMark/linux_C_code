#ifndef __PV_H_
#define __PV_H_

extern int  I(int semnums,int val);
extern void P(int semid,unsigned short sem_num,short value);
extern void V(int semid,unsigned short sem_num,short value);
extern void D(int semid);

#endif
