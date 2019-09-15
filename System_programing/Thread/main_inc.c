#include <stdio.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t count_mutex;


void increment()
{
    pthread_mutex_lock(&count_mutex);
    count++;
    pthread_mutex_unlock(&count_mutex);
}

void* threadInc()
{
    increment();
}

int main()
{
    pthread_t threadArr[10000];
    int i;
    
    for(i = 0; i < 10000; ++i)
    {
        pthread_create(&threadArr[i], NULL, threadInc, NULL);
    }

    for(i = 0; i < 10000; ++i)
    {
        pthread_join(threadArr[i], NULL);
    }

    printf("Count: %d\n", count);

    return 0;
}