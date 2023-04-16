#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define DEVICE_FILE "/dev/chardev"

int main() {
    int fd = open(DEVICE_FILE, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    char user_data[256];
    if (ioctl(fd, 1, user_data) < 0) {
        perror("ioctl");
        close(fd);
        return -1;
    }
    printf("Kernel data: %s\n", user_data);
    close(fd);
    return 0;
}
