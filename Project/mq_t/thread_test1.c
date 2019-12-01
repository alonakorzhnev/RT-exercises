#include "mq.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h> 
#include <unistd.h>

#define COUNT_OF_LOOPS 100
char* device;

pthread_mutex_t mutex_send;
pthread_mutex_t mutex_recv;

int count_send = 0;
int count_recv = 0;

void* send(void* arg)
{
    int fd;
    int ret;
    struct mq_reg message;
    char* m = "Hello";

    fd = open(device, O_RDWR);
    if(fd == -1)
    {
        fprintf(stderr, "error file name\n");
        return NULL;
    }

    message.data = m;
    message.size = strlen(m);
    
    ret = ioctl(fd, MQ_SEND_MSG, &message);
    if(ret < 0)
    {
        fprintf(stderr, "error send message\n");
        return NULL;
    }
    printf("Return value from send message %d\n", ret);

    if(close(fd) < 0)
    {
        fprintf(stderr, "error closing file\n");
        return NULL;
    }

    pthread_mutex_lock(&mutex_send);
    count_send++;
    pthread_mutex_unlock(&mutex_send);

    return NULL;
}

void* recv(void* arg)
{
    int fd;
    int ret;
    char* data;

    fd = open(device, O_RDWR);
    if(fd == -1)
    {
        fprintf(stderr, "error file name\n");
        return NULL;
    }

    data = (char*)malloc(4096);
    ret = ioctl(fd, MQ_RECV_MSG, data);
    if(ret < 0)
    {
        fprintf(stderr, "error get message\n");
        return NULL;
    }
    if(ret == 0)
    {
        fprintf(stderr, "list is empty\n");
        return NULL;
    }
    printf("Return value from get message %d\n", ret);
    printf("Message: %s\n", data);

    if(close(fd) < 0)
    {
        fprintf(stderr, "error closing file\n");
        return NULL;
    }

    pthread_mutex_lock(&mutex_recv);
    count_recv++;
    pthread_mutex_unlock(&mutex_recv);

    free(data);
    return NULL;
}

int main(int argc, char **argv)
{
    int i, j;
    pthread_t send_arr[COUNT_OF_LOOPS];
    pthread_t recv_arr[COUNT_OF_LOOPS];

    if(argc == 2)
    {
	    device = argv[1];
    }
    else 
    {
        device="/dev/mq0";
    }
    
    for (i = 0; i < COUNT_OF_LOOPS; ++i)
    {
        pthread_create(&send_arr[i], NULL, send, NULL);
        pthread_create(&recv_arr[i], NULL, recv, NULL);
    }
    for (j = 0; j < COUNT_OF_LOOPS; ++j)
    {
        pthread_join(send_arr[j], NULL);
        pthread_join(recv_arr[j], NULL);
    }

    printf("Count send = %d, count recv = %d\n", count_send, count_recv);
    return 0;
}
