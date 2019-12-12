#include <stdio.h>	// for fprintf(3), stderr:object, printf(3)
#include <stdlib.h>	// for EXIT_SUCCESS, EXIT_FAILURE
#include <time.h>	// for clock_gettime(2), clock_nanosleep(2), CLOCK_REALTIME, CLOCK_REALTIME
#include <sched.h>	// for sched_setscheduler(2), struct sched_param
#include <sys/mman.h>	// for mlockall(2)
#include <string.h>
#include <unistd.h>

/* The number of nsecs per sec. */
const long long NSEC_PER_SEC=1000000000;

/*
 * Add a number of nanoseconds to a timespec
 */
static inline void timespec_add_nanos(struct timespec* t, long long nanos_count) {
	long long nsec=t->tv_nsec+nanos_count;
	t->tv_nsec=nsec%NSEC_PER_SEC;
	t->tv_sec+=nsec/NSEC_PER_SEC;
}

/*
 * Return the diff in nanoseconds between x and y
 */
static inline unsigned long long timespec_diff_nano(struct timespec* x, struct timespec* y) {
	return (x->tv_sec-y->tv_sec)*NSEC_PER_SEC+(x->tv_nsec-y->tv_nsec);
}

int main(int argc, char** argv, char** envp) {
	if(argc != 4) {
		return EXIT_FAILURE;
	}

	const unsigned long long interval = atoi(argv[1]);
	const int priority = atoi(argv[2]);
	const unsigned int loop = atoi(argv[3]);

	struct sched_param param;
	param.sched_priority=priority;
	sched_setscheduler(0, SCHED_FIFO, &param);
	/* Lock memory */
	mlockall(MCL_CURRENT|MCL_FUTURE);

	struct timespec start_time;
	clock_gettime(CLOCK_REALTIME, &start_time);
	timespec_add_nanos(&start_time, interval);

	unsigned long long max = 0;
	unsigned long long min = 1024*1024*1024*1024LL;
	unsigned long long sum = 0;

	for(unsigned int i = 0; i < loop; i++) {
		clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &start_time, NULL);
		struct timespec current_time;
		clock_gettime(CLOCK_REALTIME, &current_time);
		unsigned long long diff_nanos = timespec_diff_nano(&current_time, &start_time);
		if(diff_nanos > max) {
			max = diff_nanos;
		}
		if(diff_nanos < min) {
			min = diff_nanos;
		}
		sum += diff_nanos;
		while(1){}
		timespec_add_nanos(&start_time, interval);
	}

	printf("max is %llu\n", max);
	printf("min is %llu\n", min);
	printf("avg is %llu\n", sum/loop);

	return EXIT_SUCCESS;
}
