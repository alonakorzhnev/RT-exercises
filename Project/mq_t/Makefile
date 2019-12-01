#this is a minimal makefile for demo purposes, keep it that way...
obj-m:=mq.o
mq-objs:=mq_main.o
V?=0
KDIR?=/lib/modules/$(shell uname -r)/build
# in an embedded system:
#KDIR:=[where the system maker gave me kernel headers+makefile or the kernel itself which has a makefile]
#ARCH:=arm
#CROSS_COMPILE:=[path+common prefix to where the toolchain is]
# You could also use W=2 and W=3 for more warnings but most kernel headers
# fail those...
W?=1

.PHONY: all
all: modules user_put user_get thread_test1 thread_test2

.PHONY: modules
modules:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) W=$(W) modules

.PHONY: clean
clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) clean
	rm -f *.stamp
	rm -f user_get user_put thread_test1 thread_test2

.PHONY: insmod
insmod:
	sudo insmod ./mq.ko
	sleep 1
	sudo chmod 666 /dev/mq*
.PHONY: rmmod
rmmod:
	sudo rmmod mq

USER_CFLAGS:=-O2 -Wall -Werror

user_put: user_put.c
	gcc $(USER_CFLAGS) -o $@ $<
user_get: user_get.c
	gcc $(USER_CFLAGS) -o $@ $<
thread_test1: thread_test1.c
	gcc $(USER_CFLAGS) -o $@ $< -pthread
thread_test2: thread_test2.c
	gcc $(USER_CFLAGS) -o $@ $< -pthread

test_insmod_rmmod: 
	@for number in $$(seq 1 100);\
	do \
	sudo insmod ./mq.ko;\
	(number=number+1);\
	sudo rmmod mq;\
	echo $$number;\
	done

test_threads1:
	@for number in $$(seq 0 7);\
	do \
	./thread_test1 /dev/mq$$number;\
	(number=number+1);\
	echo test for thread dev/mq$$number done;\
	sleep 1;\
	done

test_threads2:
	@for number in $$(seq 0 7);\
	do \
	./thread_test2 /dev/mq$$number;\
	(number=number+1);\
	echo test for thread dev/mq$$number done;\
	sleep 1;\
	done
