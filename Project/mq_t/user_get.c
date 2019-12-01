#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
#include "mq.h"

int main()
{
    int fd, ret;
    char buf[4096];

    printf("Driver open!\n");
    fd = open("/dev/mq1", O_RDWR);
    if (fd < 0)
    {
        fprintf(stderr, "Not open device\n");
        return 1;
    }
 
    printf("Read value from deriver.\n");
    ret = ioctl(fd, MQ_RECV_MSG, buf);
    if (ret < 0)
    {
        fprintf(stderr, "Error with ioctl %d\n", ret);
        return 1;
    }
    printf("size: %d\n", ret);
    printf("message: %s\n", buf);

    if (close(fd) < 0)
    {
        fprintf(stderr, "Error with close!!!\n");
        return 1;
    }
    return 0 ;
}
