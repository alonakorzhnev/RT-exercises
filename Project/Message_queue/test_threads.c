#include "mq.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>

#define LOOP_COUNT 1000

char* device;

void* send(void* arg)
{
    int fd;
    int ret;
    int i = (*(int*)arg);
    struct mq_reg message;
    char* m = "Hello";
    
    fd = open(device, O_RDWR);
    if(fd == -1)
    {
        fprintf(stderr, "error file name\n");
        return;
    }    

    message.data = m;
    message.size = strlen(m);

    ret = ioctl(fd, MQ_SEND_MSG, &message);
    if(ret < 0)
    {
        fprintf(stderr, "error send message\n");
        return;
    }
    printf("Return value from send message %d\n", ret);

    if(close(fd) < 0)
    {
        fprintf(stderr, "error closing file\n");
        return;        
    }
   
    return;
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
        return;
    }

    data = (char*)malloc(4096);
    ret = ioctl(fd, MQ_RECV_MSG, data);
    if(ret < 0)
    {
        fprintf(stderr, "error get message\n");
        return;
    }
    if(ret == 0)
    {
        fprintf(stderr, "list is empty\n");
        return;
    }
    printf("Return value from get message %d\n", ret);
    printf("Message: %s\n", data);

    if(close(fd) < 0)
    {
        fprintf(stderr, "error closing file\n");
        return;        
    }

    free(data);      
    return;
}

int main(int argc, char** argv)
{
    int senders, receivers;
    pthread_t arr_send[LOOP_COUNT];
    pthread_t arr_recv[LOOP_COUNT];
    int arr_send_id[LOOP_COUNT];
    int arr_recv_id[LOOP_COUNT];
    int i, j;

    if(argc != 2)
    {
        return 1;
    }
    device = argv[1];

    for(i = 0; i < LOOP_COUNT; ++i)
    {
        arr_send_id[i] = i;
        arr_recv_id[i] = i;
    }
    
    for(i = 0; i < LOOP_COUNT; ++i)
    {
        pthread_create(&arr_send[i], NULL, send, &arr_send_id[i]);
        pthread_create(&arr_recv[i], NULL, recv, NULL);
    }

    for(j = 0; j < LOOP_COUNT; ++j)
    {
        pthread_join(arr_send[j], NULL);
        pthread_join(arr_recv[j], NULL);
    }

    return 0;
}