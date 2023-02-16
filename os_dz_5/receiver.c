#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_BUF 1024

int main(int argc, char *argv[])
{
    int fd;
    char *fifo_name = argv[1];
    char buf[MAX_BUF];

    // Откройте именованный канал для чтения
    fd = open(fifo_name, O_RDONLY);
    printf("Receiver process: FIFO %s opened for reading\n", fifo_name);

    while (1) {
        // Считывание данных из именованного канала
        read(fd, buf, MAX_BUF);

        // Распечатать полученные данные
        printf("Received message: %s", buf);

        // Если полученные данные имеют значение "exit", выйдите из цикла.
        if (strncmp(buf, "exit", 4) == 0) {
            break;
        }
    }

    // Закройте именованный канал
    close(fd);
    printf("Receiver process: FIFO %s closed\n", fifo_name);

    return 0;
}
