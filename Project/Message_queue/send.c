#include "mq.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    int fd;
    int ret;
    struct mq_reg message;
    if(argc != 3)
    {
        return 1;
    }
    
    fd = open(argv[1], O_RDWR);
    if(fd == -1)
    {
        fprintf(stderr, "error file name\n");
        return 1;
    }    

    message.data = (char*)malloc(sizeof(char)*(strlen(argv[2]) + 1));
    strcpy(message.data, argv[2]);
    message.size = strlen(argv[2]);

    ret = ioctl(fd, MQ_SEND_MSG, &message);
    if(ret < 0)
    {
        fprintf(stderr, "error send message\n");
        return 1;
    }
    printf("Return value from send message %d\n", ret);

    if(close(fd) < 0)
    {
        fprintf(stderr, "error closing file\n");
        return 1;        
    }
     
    return 0;
}