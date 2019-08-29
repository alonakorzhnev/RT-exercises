#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> 

int main()
{
    pid_t pid;
    char *arg[] = {NULL, NULL};
    int status;
    char buffer[32];

    while(1)
    {
        printf("->");
        scanf("%s", buffer);

        if(strcmp(buffer, "exit") == 0)
            return 0;

        arg[0] = buffer;

        pid = fork();
        if(pid == -1)
        {
            printf("Error in fork!\n");
            return 0;
        }
        else if(pid == 0)
        {
            execv(arg[0], arg);
        }
        else
        {
            waitpid(pid, &status, 0);
        }        
    }   

    return 0;
}


