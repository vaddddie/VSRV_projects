#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSZ 512

struct msg
{ /* Структура сообщения */
   long msg_type;
   char msg_text[BUFSZ];
};

int main(int argc, char *argv[])
{
    int qid; /* Идентификатор очереди */
    int len; /* Размер сообщения */
    struct msg pmsg; /* Указатель на сообщение */

    if(argc != 2)
    {  /* ID должен быть передан в командной строке */
        puts("USAGE: qsnd <queue ID>");
        exit(EXIT_FAILURE);
    }

    qid = atoi(argv[1]);
    puts("Enter message to post:"); /* Получить сообщение для записи в очередь */

    if((fgets((&pmsg) ->msg_text, BUFSZ, stdin)) == NULL)
    {
        puts("no message to post");
        exit(EXIT_SUCCESS);
    }

    pmsg.msg_type = getpid(); /* Связать тип сообщения с pid процесса */
    len = strlen(pmsg.msg_text); /* Добавить сообщение в очередь */

    if((msgsnd(qid, &pmsg, len, 0)) < 0)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    puts("message posted");
    exit(EXIT_SUCCESS);
}
