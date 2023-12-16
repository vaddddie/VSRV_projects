#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_NUMBER 100
#define NUMBER_OF_ITERATION 10

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t got_request_even = PTHREAD_COND_INITIALIZER; // чётное
pthread_cond_t got_request_odd = PTHREAD_COND_INITIALIZER;  // нечётное

int number;

void* generator()
{
    for (int i = 0; i < NUMBER_OF_ITERATION; i++)
    {
        pthread_mutex_lock(&mutex);

        number = rand() % MAX_NUMBER;
        if (number % 2 == 0)
        {
            pthread_cond_signal(&got_request_even);
        }
        else
        {
            pthread_cond_signal(&got_request_odd);
        }
        printf("The number %d has been sent\n", number);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
}

void* square()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&got_request_even, &mutex);
        printf("The square of the number: %d\n", number*number);
        pthread_mutex_unlock(&mutex);
    }
}

void* cube()
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&got_request_odd, &mutex);
        printf("The cube of a number: %d\n", number*number*number);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t gen_addr, sqr_addr, cub_addr;

    pthread_create(&sqr_addr, NULL, square, NULL);
    pthread_create(&cub_addr, NULL, cube, NULL);
    pthread_create(&gen_addr, NULL, generator, NULL);

    pthread_join(gen_addr, NULL);

    return 0;
}
