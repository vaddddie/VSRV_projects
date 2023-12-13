#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */
#include <stdlib.h>
#include <unistd.h> 

/* function to be executed by the new thread */
void* PrintHello(void* data)
{
    pthread_t tid = *(pthread_t*)data;     	/* data received by thread */
    pthread_join(tid, NULL);
    printf("Hello from new thread %lu - got %lu\n", pthread_self(), tid);
    pthread_exit(NULL);
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
    pthread_t tid = pthread_self();

    int        rc;         	/* return value                           */
    pthread_t  thread_id;     	/* thread's ID (just an integer)          */
    
    /* create a new thread that will execute 'PrintHello' */
    rc = pthread_create(&thread_id, NULL, PrintHello, (void*)tid);
    if(rc)			/* could not create thread */
    {
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }

    sleep(1);

    printf("\n I am thread %lu. Created new thread (%lu) ... \n", tid, thread_id);

    pthread_exit(NULL);
}

