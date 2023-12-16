#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUMBER_OF_DAYS 5
#define NUMBER_OF_CATS 5

#define MAX_FOOD 1000
#define PORTION_OF_FOOD 100
#define MIN_LIMIT_OF_FOOD 300

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t got_request = PTHREAD_COND_INITIALIZER;

int food = MAX_FOOD;

void* owner()
{
    int added_feed;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&got_request, &mutex);

        if (food < MIN_LIMIT_OF_FOOD)
        {
            added_feed = MAX_FOOD - food - rand() % 50;
            food += added_feed;
            printf("The owner added %d grams of feed; food: %d\n", added_feed, food);
        }

        pthread_mutex_unlock(&mutex);
    }
}

void* cat()
{
    int portion;
    for (int i = 0; i < NUMBER_OF_DAYS; i++)
    {
        pthread_mutex_lock(&mutex);
        portion = PORTION_OF_FOOD + (rand() % 10) - 5;
        food -= portion;
        printf("Day number %d; The cat ate %d grams of feed; food: %d\n", i + 1, portion, food);
        pthread_cond_signal(&got_request);
        pthread_mutex_unlock(&mutex);

        sleep(1 + (rand() % 10) / 10);
    }
}

int main()
{
    pthread_t owner_addr, cats_addr[NUMBER_OF_CATS];

    pthread_create(&owner_addr, NULL, owner, NULL);

    for (int i = 0; i < NUMBER_OF_CATS; i++)
    {
        pthread_create(&cats_addr[i], NULL, cat, NULL);
    }

    for (int i = 0; i < NUMBER_OF_CATS; i++)
    {
        pthread_join(cats_addr[i], NULL);
    }

    return 0;
}
