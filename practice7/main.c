#include <stdio.h>
#include "dbg.h"
 
int main(void) {
    puts("This is a shared library test...");
    int shmid = dbg_init();
    printf("shmid=%d\n", shmid);

    char* buffer = "hello1\n";
    printf("Data writing to shm: %s", buffer);
    dbg_write(shmid, buffer, sizeof(buffer));

    char* msg = dbg_read(shmid);
    printf("Data read from shm: %s", msg);
    dbg_close(shmid);
    
    return 0;
}
