#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_MESSAGE 100
#define MESSAGE_COUNT 3
#define TRANSCEIVER_COUNT 2

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t got_request = PTHREAD_COND_INITIALIZER;
int channel[5];
int num_requests = 0;

void* transceiver()
{
    for (int i = 0; i < MESSAGE_COUNT; i++)
    {
        int new_message = rand() % MAX_MESSAGE;
        pthread_mutex_lock(&mutex);
        channel[num_requests++] = new_message;
        printf("The message has been sent: %d\n", new_message);
        pthread_cond_signal(&got_request);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}

void* receiver()
{
    int rc;

    while(1)
    {
        rc = 0;
        pthread_mutex_lock(&mutex);
        if (num_requests == 0)
        {
            rc = pthread_cond_wait(&got_request, &mutex);
        }
        if (num_requests > 0 && rc == 0)
        {
            int message = channel[--num_requests];
            printf("The message has been reciived: %d\n", message);
        }
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t trans[TRANSCEIVER_COUNT];
    pthread_t rec;

    for (int i = 0; i < TRANSCEIVER_COUNT; i++)
    {
        pthread_create(&trans[i], NULL, transceiver, NULL);
    }
    pthread_create(&rec, NULL, receiver, NULL);

    for (int i = 0; i < TRANSCEIVER_COUNT; i++)
    {
        pthread_join(trans[i], NULL);
    }

    return 0;
}


