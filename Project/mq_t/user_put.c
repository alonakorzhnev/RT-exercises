#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "mq.h"

int main(int argc, char** argv, char** envp)
{
    int fd, ret;
    struct mq_reg buf;
    char *str;

    if(argc>1) {
	str=argv[1];
    } else {
        str="hello";
    }

    buf.size = strlen(str);
    buf.data = str;

    printf("Driver open!\n");
    fd = open("/dev/mq1", O_RDWR);
    if (fd < 0)
    {
        fprintf(stderr, "Not open device!\n");
        return 1;
    }

    printf("Write value to deriver.\n");
    ret=ioctl(fd, MQ_SEND_MSG, &buf);
    if(ret<0)
    {
        fprintf(stderr, "Error with ioctl!\n");
        return 1;
    }
    printf("got %d from ioctl\n", ret);

    if (close(fd) < 0)
    {
        fprintf(stderr, "Error with close!!!\n");
        return 1;
    }
    return 0;
}