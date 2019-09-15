#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mut;

void* threadRun(void *param)
{   
    printf("My id = %d\n", (*(int*)param)); 
    (*(int*)param)++;
    sem_post(&mut);
}

int main()
{
    pthread_t threadArr[1000];
    int i = 0, j = 0;
    sem_init(&mut, 0, 1);
    
    while(i < 1000)
    {
        sem_wait(&mut);
        pthread_create(&threadArr[i], NULL, threadRun, &i);      
    }

    for(j = 0; j < 1000; ++j)
    {
        pthread_join(threadArr[j], NULL);
    }

    sem_destroy(&mut); 
    return 0;
}