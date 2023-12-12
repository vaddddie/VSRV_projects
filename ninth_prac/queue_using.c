#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Для простоты, ограничимся записями фиксированной длины. */
struct message
{
    long int mtype;
    char mtext[128];
};

/* Формируем текст сообщения и посылаем его в очередь. */
int send_msg(int qid, int mtype, const char text[])
{
    struct message msg = { .mtype = mtype };
    strncpy(msg.mtext, text, sizeof(msg.mtext));
    int r = msgsnd(qid, &msg, sizeof(msg), 0);

    if (r == -1) {
        perror("msgsnd");
    }

    return r;
}

/* Читаем сообщение из очереди в структуру, определенную пользователем */
int recv_msg(int qid, int mtype, struct message *msg)
{
    int r = msgrcv(qid, msg, sizeof(struct message), mtype, 0);

    switch (r)
    {
        case sizeof(struct message):
            break;
        /* okay */
        case -1:  perror("msgrcv");
            break;
        default: printf("only received %d bytes\n", r);
    } //end switch

    return r;
} //end recv_msg

void producer(int mqid) /* Для процесса “производилеля” */
{
    /* Обратите внимание на порядок, в котором мы посылаем сообщения. */
    send_msg(mqid, 1, "type 1 - first");
    send_msg(mqid, 2, "type 2 - second");
    send_msg(mqid, 1, "type 1 - third");
}
void consumer(int qid) /* Для процесса “потребителя” */
{
    struct message msg; int r;
    int i;
    for (i = 0; i < 3; i++)
    {
        /* параметр -2 для считывания всех сообщений типа 2 или меньше. */
        r = msgrcv(qid, &msg, sizeof(struct message), -2, 0);
        printf("'%s'\n", msg.mtext);
    }
}

int main(int argc, char *argv[])
{
    /* Создание частной (неименованной) очереди сообщений. */
    int mqid;
    mqid = msgget(IPC_PRIVATE, S_IREAD | S_IWRITE);

    if (mqid == -1)
    {
        perror("msgget");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == 0)
    {
        consumer(mqid);
        exit(0);
    }
    else
    {
        int status;
        producer(mqid);
        wait(&status);
    }

    /* Удаление очереди сообщений. */
    int r = msgctl(mqid, IPC_RMID, 0);
    if (r) perror("msgctl");
    return 0;
}
