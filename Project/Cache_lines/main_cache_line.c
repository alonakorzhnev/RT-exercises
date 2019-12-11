#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmodule.h> /* linked_list */
#include <unistd.h> /* file open */
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h> 

GSList* list = NULL;

pthread_mutex_t lock_list;
sem_t fill_count;
sem_t empty_count;
const int message_size = 20;
pthread_mutex_t lock_count;
int message_count = 0;

void* counter()
{
    while(1)
    {
        sleep(60);
        pthread_mutex_lock(&lock_count);
        printf("%d messeges per minute\n", message_count);
        message_count = 0;
        pthread_mutex_unlock(&lock_count);
    }

    return NULL;
}

void* produser()
{
    char* random_data, *ptr;
    int ret, my_data;

    int fd = open("/dev/urandom", O_RDONLY);
    if(fd < 0)
    {
        perror("Error in open file\n");
        return NULL;
    }

    ret = posix_memalign((void**)&random_data, 64, message_size + 1);

    while(1)
    {
        my_data = 0;
        ptr = random_data;
        do
        {
            ret = read(fd, ptr, message_size - my_data);
            if(ret < 0)
            {
                perror("Error in read file\n");
                return NULL;        
            }
            my_data += ret;
            ptr += ret;
        }while(my_data < message_size);       

        sem_wait(&empty_count);
        pthread_mutex_lock(&lock_list);

        list = g_slist_prepend(list, random_data);

        pthread_mutex_unlock(&lock_list);
        sem_post(&fill_count);
    }

    ret = close(fd);
    if(ret < 0)
    {
        perror("Error in close file\n");
        return NULL;        
    }

    return NULL;
}

void* consumer()
{
    char* data_from_list;
    GSList* node;

    while(1)
    {
        sleep(1);
        sem_wait(&fill_count);
        pthread_mutex_lock(&lock_list);

        node = g_slist_last(list);
        

        pthread_mutex_unlock(&lock_list);
        sem_post(&empty_count);

        pthread_mutex_lock(&lock_count);
        message_count++;
        pthread_mutex_unlock(&lock_count);
    }

    return NULL;
}

int main()
{
    int i;
    cpu_set_t cpuset;
    pthread_attr_t attr;
    pthread_t produser_t;
    pthread_t consumer_t[2];
    pthread_t counter_t;

    sem_init(&fill_count, 0, 0);
    sem_init(&empty_count, 0, 50);

    pthread_attr_init(&attr);
    CPU_ZERO(&cpuset);
    CPU_SET(3, &cpuset);
    pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
    pthread_create(&produser_t, &attr, &produser, NULL);

    for(i = 1; i <= 2; i++)
    {
        CPU_ZERO(&cpuset);
        CPU_SET(i, &cpuset);
        pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
        pthread_create(&consumer_t[i], &attr, &consumer, NULL);
    }

    CPU_SET(3, &cpuset);
    pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);
    pthread_create(&counter_t, &attr, &counter, NULL);

    pthread_join(produser_t, NULL);
    for(i = 0; i < 2; i++)
    {
        pthread_join(consumer_t[i], NULL);
    }

    return EXIT_SUCCESS;
}