#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int semid; /* Идентификатор семафора */
    int nsems = 1; /* Количество семафоров в создаваемом наборе */
    int flags = 0666; /* Права доступа к семафорам */

    struct sembuf buf;

    /* Создание набора семафоров с требуемыми правами доступа*/
    semid = semget(IPC_PRIVATE, nsems, flags);

    if(semid < 0)
    {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    printf("semaphore created: %d\n", semid);
    /* Подготовка структуры для инициализации семафора */
    buf.sem_num = 0;
    buf.sem_op = 1;
    buf.sem_flg = IPC_NOWAIT;

    if((semop(semid, &buf, nsems)) < 0)
    {
        perror("semop");
        exit(EXIT_FAILURE);
    }
    system("ipcs -s"); /* Проверка наличия семафора в ресурсах ядра */
    exit(EXIT_SUCCESS);
}
