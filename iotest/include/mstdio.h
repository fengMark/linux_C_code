#ifndef _MSTDIO_H_
#define _MSTDIO_H_

#define MEOF -1
#include<sys/types.h>
enum mode{READ,WRITE,APPEND};

typedef struct{
int _fd;
char *_buffer;//緩存
char *_nextc;//指向字符
int _mode;//方式
off_t _left;//統計緩存字符
}MFILE;

extern MFILE* mfopen(const char * const pathname,const char * *const mode);
extern MFILE* mfdopen(int fd,
const char * const mode);
extern int mfclose(MFILE * fp);
extern void mfflush(MFILE *fp);




extern int mfgetc(MFILE *fp);
extern int mfputc(MFILE *fp);
extern int mungetc(int character,MFILE *fp);

extern char * mfgets(char *buff,int size ,MFILE *fp);
extern int mfputs(char *buff,MFILE *fp);


extern size_t mfread(void *buff,size_t size,
size_t counter,MFILE *fp);
extern size_t mfwrite(void *buff,size_t size,
size_t counter,MFILE *fp);



#endif
