#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFSZ 4096

int main(int argc, char *argv[])
{
    int shmid;  /* ID сегмента */
    char *shmbuf; /* Адрес в адресном пространстве процесса */
    int fd; /* Файловый дескриптор */
    int i; /* Счетчик */

    if(argc != 2)
    { /* id сегмента должно передаваться в командной строке */
        puts("USAGE: opshm <identifier>");
        exit (EXIT_FAILURE);
    }

    shmid = atoi(argv[1]);
    if((shmbuf = shmat(shmid, 0, 0)) < (char *)0)
    { /* Присоединяем сегмент */
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    if((shmbuf = malloc(sizeof(char) * BUFSZ)) == NULL)
    { /* Резервируем память для shmbuf */
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for(i = 0; i < BUFSZ; ++i) {shmbuf[i] = i % 127;}

    fd = open("opshm.out", O_CREAT | O_WRONLY, 0600);
    write(fd, shmbuf, BUFSZ);
    exit(EXIT_SUCCESS);
}
