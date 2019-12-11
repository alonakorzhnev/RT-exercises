
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

const int max_events = 10;
const int max_buff = 4096;
const int port = 8080;

const int max_fds = 10;
const char* buffers_to_write[10];
int count_to_write[10];

const char *response =
"HTTP/1.1 200 OK\n"
"\n";

void check_error(int val) 
{
	if(val == -1)
	{
		perror("myserver");
		exit(1);
	}
}

void write_to_fd(int fd, const char* buff, int size) 
{
	int written = 0;
	const char* pos = buff;
	while(written < size) 
	{
		written += write(fd, pos, size - written);
		pos += written;
	}
}

void read_from_fd(int fd, char* buff, int size) 
{
	int read_size = 0;
	char* pos = buff;
	while(read_size < size) 
	{
		read_size += read(fd, pos, size - read_size);
		pos += read_size;
	}
}

char* get_file_name(char* str)
{
	int i = 0, j = 0;
	char* filename= malloc(26);
	while(i < strlen(str))
	{
		if(str[i] == '/')
		{
			i++;
			while(str[i] != ' ')
			{
				filename[j] = str[i];
				j++;
				i++;
			}
			filename[j] = '\0';
			printf("%s\n", filename);
			return filename;
		}
		i++;
	}
	return NULL;
}

int main()
{
	socklen_t len;
	struct sockaddr_in servaddr, cli;

	/* socket create and verification */
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	check_error(sockfd);
	printf("Socket successfully created..\n");

	int optval=1;
	check_error(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)));

	/* assign IP, port */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	/* Binding newly created socket to given IP and verification */
	check_error(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)));
	printf("Socket successfully binded..\n");

	/* Now server is ready to listen and verification */
	check_error(listen(sockfd, 5));
	printf("Server listening..\n");
	len = sizeof(cli);

	int epollfd = epoll_create1(0);
	check_error(epollfd);

	struct epoll_event event;
	event.data.fd = sockfd;
	event.events = EPOLLIN;
	check_error(epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &event));

	while(1) 
    {
		struct epoll_event all_events[max_events];
		int num_events = epoll_wait(epollfd, all_events, max_events, -1);
		check_error(num_events);
		for(int i = 0; i < num_events; i++) 
        {
			int fd = all_events[i].data.fd;
			uint32_t events = all_events[i].events;                        
			if(fd == sockfd) 
            {
				int connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
				check_error(connfd);
				printf("server acccept the client...\n");
				//struct epoll_event event;
				event.data.fd = connfd;
				event.events = EPOLLIN;
				check_error(epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &event));
			} else 
            {
				if(events & EPOLLIN) 
                {
					char buf[4096];
					ssize_t bytes_read = read(fd, buf, 4096);
					buf[bytes_read] = '\0';

					printf("buf is %s\n", buf);
					printf("bytes_read is %ld\n", bytes_read);
                    
					struct epoll_event event;
					event.data.fd = fd;
					event.events = EPOLLOUT;
					check_error(epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event));

                    char* filename = get_file_name(buf);

                    /* find the size of the file */
                    struct stat statbuf;
                    check_error(stat(filename, &statbuf));
                    int file_size = statbuf.st_size;

                    char* file_content = (char*)malloc(file_size);
                    int fd = open(filename, O_RDONLY);
                    check_error(fd);
                    read_from_fd(fd, file_content, file_size);
                    check_error(close(fd));

                    char* page_content = (char*)malloc(file_size + sizeof(response) + 1);
                    strcpy(page_content, response);
                    strcat(page_content, file_content);
                    page_content[file_size + sizeof(response)] = 0;

					buffers_to_write[fd] = page_content;
					count_to_write[fd] = strlen(page_content);
                    //free(page_content);
				}
				if(events & EPOLLOUT) 
                {
					ssize_t bytes_written = write(fd, buffers_to_write[fd], count_to_write[fd]);
					check_error(bytes_written);
					buffers_to_write[fd] += bytes_written;
					count_to_write[fd] -= bytes_written;
					if(count_to_write[fd] == 0) 
                    {
						struct epoll_event event;
						event.data.fd = fd;
						check_error(epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, &event));
						check_error(close(fd));
					}
				}
			}
		}
	}
	check_error(close(sockfd));
	check_error(close(epollfd));
	return EXIT_SUCCESS;
}
