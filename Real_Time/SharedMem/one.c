#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>

int main()
{
    key_t key = ftok("key1", 65);
    int shmid = shmget(key, (size_t)1024, 0666|IPC_CREAT);
    int* myint = (int*)shmat(shmid, 0, 0);
    *myint = 0;

    while(1)
    {
        *myint +=1;
        printf("%d\n", *myint);
        sleep(1);
    }

    shmdt(myint);
    return 0;
}

