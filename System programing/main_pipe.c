#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main()
{
    char writeBuffer[32];
    char readBuffer[32];
    pid_t pid;
    int fd[2];

    pipe(fd);
    pid = fork();

    if(pid > 0)
    {
        strcpy(writeBuffer, "Hello son!\n");
        write(fd[1], writeBuffer, sizeof(writeBuffer));
        wait(&pid);
        read(fd[0], readBuffer, sizeof(readBuffer));
        printf("%s", readBuffer);            
    }
    else
    {
        read(fd[0], readBuffer, sizeof(readBuffer));
        printf("%s", readBuffer);

        strcpy(writeBuffer, "Hello father!\n");
        write(fd[1], writeBuffer, sizeof(writeBuffer));       
    }

    return 0;
}