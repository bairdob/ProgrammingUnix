#ifndef dbg_h__
#define dbg_h__
 
extern int dbg_init(void);
extern void dbg_write(int shmid, char* buffer, int length);
extern char* dbg_read();
extern void dbg_close(int shmid);
 
#endif  // dbg_h__
