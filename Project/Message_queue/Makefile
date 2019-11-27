# this is a minimal makefile for demo purposes, keep it that way...
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
.PHONY: modules
modules:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) W=$(W) modules
.PHONY: clean
clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) V=$(V) clean
	rm -f *.stamp

.PHONY: insmod
insmod:
		sudo insmod ./mq.ko
		sleep 1
		sudo chmod 666 /dev/mq*

.PHONY: rmmod
rmmod:
		sudo rmmod mq

.PHONY: remod
remod: rmmod insmod

send: send.c
		gcc -pedantic -ansi -O2 -o $@ $< -g

get: get.c
		gcc -pedantic -ansi -O2 -o $@ $< -g

test_threads: test_threads.c
		gcc -pedantic -ansi -O2 -o $@ $< -g -pthread

test1:
	for number in $$(seq 1 100);\
	do \
	sudo insmod mq.ko;\
	sleep 1 ;\
	sudo chmod 666 /dev/mq*;\
	sudo rmmod mq;\
	(number=number+1);\
	echo test iteration number $$number done;\
	done

test2:
	for number in $$(seq 0 7);\
	do \
	./test_threads /dev/mq$$number;\
	(number=number+1);\
	echo test iteration dev/mq$$number done;\
	sleep 1 ;\
	done
