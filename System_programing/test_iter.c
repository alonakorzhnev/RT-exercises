#include <stdio.h>
#include <pthread.h>

int j = 0;

void* threadf(void *param)
{
    ++j;   
}

int main()
{
    pthread_t arr[35500];
    int i, k;

    for(i = 0; i < 35500; ++i)
    {
        pthread_create(&arr[i], NULL, threadf, NULL);
    }

    for(k = 0; k < 35500; ++k)
    {
        pthread_join(arr[k], NULL);   
    }

    printf("%d\n", j);
}
