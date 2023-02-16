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

    // Создайте именованный канал (FIFO), если он еще не существует
    mkfifo(fifo_name, 0666);

    // Откройте именованный канал для записи
    fd = open(fifo_name, O_WRONLY);
    printf("Sender process: FIFO %s opened for writing\n", fifo_name);

    while (1) {
        // Получить входные данные от пользователя
        printf("Enter message: ");
        fgets(buf, MAX_BUF, stdin);

        // Записать входные данные в именованный канал
        write(fd, buf, strlen(buf)+1);

        // Если пользователь вводит "exit", выйдите из цикла
        if (strncmp(buf, "exit", 4) == 0) {
            break;
        }
    }

    // Закройте именованный канал
    close(fd);
    printf("Sender process: FIFO %s closed\n", fifo_name);

    // Удалить именованный канал
    unlink(fifo_name);
    printf("Sender process: FIFO %s removed\n", fifo_name);

    return 0;
}
