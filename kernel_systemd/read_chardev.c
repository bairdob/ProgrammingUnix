#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    while(1){
        int fd;
        char buff[100];
        FILE *pFile;
        pFile=fopen("chardev.log", "a");
    
        fd = open("/dev/chardev", O_RDWR);
        read(fd, buff, 20);
        buff[20]=0;
        printf("Reading data from kernel. Data: %s", buff);
            
        fprintf(pFile, "%s", buff);
        fclose(pFile);

        close(fd);
    }

    return 0;

}
