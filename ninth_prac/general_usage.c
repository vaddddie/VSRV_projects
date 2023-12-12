#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

void error_out(const char *msg)
{
    perror(msg); exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    key_t mykey = 12345678; /* ключ для использования сегмента общей памяти */
    /* Используется сегмент в одну страницу */
    const size_t region_size = sysconf(_SC_PAGE_SIZE);

    /* Создание сегмента общей памяти */
    int smid = shmget(mykey, region_size, IPC_CREAT | 0666);
    if (smid == -1) {error_out("shmget");}

    /* Присоединение сегмента общей памяти */
    void *ptr;
    ptr = shmat(smid, NULL, 0);
    if (ptr == (void *) -1) {error_out("shmat");}

    /* Порождение нового процесса */
    pid_t pid = fork();
    if (pid == 0)
    { /* Процесс потомок наследует отображение памяти */
        u_long *d = (u_long *) ptr;
        *d = 0xdeadbeef; /* потомок производи запись данных в сегмент */
        exit(0);
    }
    else
    {
        /* Синхронизация с потомком через waitpid */
        int status;
        waitpid(pid, &status, 0);
        /* Родитель использует значение из общей памяти */
        printf("child wrote %#lx\n", *(u_long *) ptr);
    }

    /* По окончании, отсоединяем сегмент */
    int r = shmdt(ptr);
    if (r == -1) {error_out("shmdt");}

    /* Удаляем сегмент из ресурсов ядра */
    r = shmctl(smid, IPC_RMID, NULL);
    if (r == -1) {error_out("shmdt");}

    return 0;
}
