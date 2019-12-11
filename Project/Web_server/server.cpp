#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/epoll.h>

void ERR(int errcode, const char* msg) {
	if (errcode==-1) {
		perror(NULL);
		fprintf(stderr, "%s\n", msg);
		exit(1);
	}
}

class Reactor {
    public:
        Reactor() {
            socket_init();
            epoll_init();
        }
        int socket_init();
        int epoll_init();
        void init_buffer_manager();
        void loop();

    private:
        int socket_fd;
        int epoll_fd;

};

class FD_handler {
    public:
        virtual void handle(int fd);

    private:
        int connection_fd;

};

class Connection_FD_handler: public FD_handler {
    public:
        virtual void handle_in(int fd);
        virtual void handle_out(int fd);

    private:
        int read_request(int fd, int epoll_fd);
        int message_has_ended(int fd);
};

class Socket_FD_handler: public FD_handler {
    public:
        int accept_request(int socket_fd, int epoll_fd);

};