#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>

int main()
{
    key_t key = ftok("key", 65);
    if(key == -1)
    {
        perror("ftok");
        exit(1);
    }

    int shmid = shmget(key, sizeof(int), 0666|IPC_CREAT);
    int* myint = (int*) shmat(shmid, (void*)0, 0);
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

