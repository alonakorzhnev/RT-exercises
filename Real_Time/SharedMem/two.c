#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>

int main()
{
    key_t key = ftok("key", 65);
    int shmid = shmget(key, (size_t)1024, 0666|IPC_CREAT);
    int* myint = (int*) shmat(shmid, (void*)0, 0);

    while(1)
    {
        printf("the value is %d\n", *myint);
        sleep(1);
    }
    shmdt(myint);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
