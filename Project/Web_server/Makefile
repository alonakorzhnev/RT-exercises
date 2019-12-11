my_server_thread: my_server_thread.c
	gcc -O2 -Wall -Werror -pedantic -o $@ $< -pthread

my_server_epoll: my_server_epoll.c
	gcc -O2 -Wall -pedantic -o $@ $< -pthread

server2: server2.c
	gcc -O2 -Wall -pedantic -o $@ $< -pthread

.PHONY: clean
clean:
	rm -f my_server_thread my_server_epoll server2
