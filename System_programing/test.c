#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mut1;
sem_t mut2;
sem_t mut3;


void* thread1(void *param)
{
    while(1)
    {
        sem_wait(&mut1);
        printf("%c", '1');
        sem_post(&mut2);
    }    
}

void* thread2(void *param)
{
    while(1)
    {
        sem_wait(&mut2);
        printf("%c", '2');
        sem_post(&mut3);
    }
}

void* thread3(void *param)
{
    while(1)
    {   sem_wait(&mut3);
        printf("%c", '3');
        sem_post(&mut1);
    }
}


int main()
{
    pthread_t threadPtr1, threadPtr2, threadPtr3;

    sem_init(&mut1, 0, 1);
    sem_init(&mut2, 0, 0);
    sem_init(&mut3, 0, 0);

    
    pthread_create(&threadPtr1, NULL, thread1, NULL);
    pthread_create(&threadPtr2, NULL, thread2, NULL);
    pthread_create(&threadPtr3, NULL, thread3, NULL);

    pthread_join(threadPtr1, NULL);
    pthread_join(threadPtr2, NULL);
    pthread_join(threadPtr3, NULL);
}