#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int shmid; /* Идентификатор сегмента */
    char *shmbuf; /* Адрес в адресном пространстве процесса */

    if(argc != 2)
    { /* id сегмента должно передаваться в командной строке */
        puts("USAGE: atshm <identifier>");
        exit(EXIT_FAILURE);
    }

    shmid = atoi(argv[1]);

    if((shmbuf = shmat(shmid, 0, 0)) < (char *)0)
    { /* Присоединение сегмента */
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("segment attached at %p\n", shmbuf); /* Где он реально присоединен? */

    system("ipcs -m"); /* Проверим присоединение! */

    if((shmdt(shmbuf)) < 0)
    { /* Отсединяем */
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    puts("segment detached\n");
    system("ipcs -m"); /* Приверим отсоединение */

    exit(EXIT_SUCCESS);
}
