CFLAGS=-g -Wall -Werror -O2 -pedantic $(shell pkg-config --cflags glib-2.0)

LDFLAGS=$(shell pkg-config --libs glib-2.0)

cache_align: cache_align.c
	gcc $(CFLAGS) -o $@ $< $(LDFLAGS) -lpthread
	
.PHONY: clean

clean:
	rm -f main
