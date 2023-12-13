#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */
#include <stdlib.h>
#include <unistd.h>

/* function to be executed by the new thread */
void* PrintHello(void* data)
{
    int iter = (int)data;     	/* data received by thread */
    pthread_detach(pthread_self());
    printf("Hello from new thread %lu - I was created in iteration %d...\n", pthread_self(), iter);
    pthread_exit(NULL);
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("USAGE: <number of threads>\n");
        return 1;
    }

    int number_threads = atoi(argv[1]);
    int        rc;         	/* return value                           */
    pthread_t  thread_id;     	/* thread's ID (just an integer)          */
    pthread_t tid = pthread_self();

    for (int i = 0; i < number_threads; i++)
    {
        rc = pthread_create(&thread_id, NULL, PrintHello, (void*)i);
        if(rc)			/* could not create thread */
        {
            printf("\n ERROR: return code from pthread_create is %d \n", rc);
            exit(1);
        }

        printf("I am thread %lu. Created new thread (%lu) in iteration %d\n", tid, thread_id, i);

        if (i % 5 == 0)
        {
            sleep(1);
        }

    }

    pthread_exit(NULL);
}


