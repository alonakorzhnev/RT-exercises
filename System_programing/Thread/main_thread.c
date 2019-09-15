#include <stdio.h>
#include <pthread.h>


void* fthread1(void* param)
{
    int i;

    printf("Thread1 param: %d\n", (*(int*)param));

    for(i = 0; i < 5; ++i)
    {
        printf("Thread 1\n");
        sleep(2);
    }

    pthread_exit(0);
}

void* fthread2(void* param)
{
    int i;

    printf("Thread2 param: %d\n", (*(int*)param));

    for(i = 0; i < 3; ++i)
    {
        printf("Thread 2\n");
        sleep(3);
    }
}

int main()
{
    pthread_t thread1, thread2;
    int param1 = 11, param2 = 12;
    void *status;

    pthread_create(&thread1, NULL, fthread1, &param1);
    pthread_create(&thread2, NULL, fthread2, &param2);

    pthread_join(thread1, &status);
    /*printf("Thread1 retVal: %d\n", (*(int*)status));*/

    pthread_join(thread2, NULL);

    return 0;
}