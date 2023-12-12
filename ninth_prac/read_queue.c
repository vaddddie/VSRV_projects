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
    /* Получить и отобразить сообщение из очереди */
    len = msgrcv(qid, &pmsg, BUFSZ, 0, 0);

    if(len > 0)
    {
        printf("reading queue id: %05d\n", qid);
        printf("\tmessage type: %05ld\n", (&pmsg) ->msg_type);
        printf("\tmessage text: %s\n", (&pmsg) ->msg_text);
    }
    else
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
