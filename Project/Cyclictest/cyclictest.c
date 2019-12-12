#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <sys/mman.h>
#include <string.h>
#include <limits.h>

const unsigned int nsec_per_sec = 1000000000;

void timespec_add_ns(struct timespec* t, unsigned long long ns){
	unsigned long long nsec = t->tv_nsec + ns;
	t->tv_nsec = nsec%nsec_per_sec;
	t->tv_sec += nsec/nsec_per_sec;
}

unsigned long long timespec_diff_ns(struct timespec* t1, struct timespec* t2){
	struct timespec diff;
	diff.tv_sec = t1->tv_sec - t2->tv_sec;
	diff.tv_nsec = t1->tv_nsec - t2->tv_nsec;	
	return diff.tv_sec*nsec_per_sec + diff.tv_nsec;
}

void ERR(int errcode, const char* msg){
	if(errcode != 0){
		perror(NULL);
		fprintf(stderr, "%s\n", msg);
		exit(1);
	}
}

int main(int argc, char** argv, char** envp){
	if(argc != 4){
		return EXIT_FAILURE;
	}

	// get arguments
	const unsigned long long interval = atoi(argv[1]);
	const int priority = atoi(argv[2]);
	const unsigned int count_iter = atoi(argv[3]);

	// set priority and scheduling policy
	struct sched_param param;
	param.sched_priority = priority;
	ERR(sched_setscheduler(0, SCHED_FIFO, &param), "sched_setscheduler");

	// lock memory from page faults
	ERR(mlockall(MCL_CURRENT|MCL_FUTURE), "mlockall");

	// get current time
	struct timespec start_time;
	ERR(clock_gettime(CLOCK_REALTIME, &start_time), "clock_gettime");
	timespec_add_ns(&start_time, interval);

	unsigned long long time_max = 0;
	unsigned long long time_min = ULLONG_MAX;
	unsigned long long time_sum = 0;
	unsigned long long time_difference = 0;

	for(unsigned int i = 0; i < count_iter; ++i){
		ERR(clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &start_time, NULL), "clock_nanosleep");
		struct timespec current_time;
		ERR(clock_gettime(CLOCK_REALTIME, &current_time), "clock_gettime");

		time_difference = timespec_diff_ns(&current_time, &start_time);		
		if(time_difference > time_max){
			time_max = time_difference;
		}
		if(time_difference < time_min){
			time_min = time_difference;
		}
		time_sum += time_difference;

		timespec_add_ns(&start_time, interval);
	}

	printf("time max: %llu\n", time_max);
	printf("time min: %llu\n", time_min);
	printf("time avg: %llu\n", time_sum/count_iter);

	return EXIT_SUCCESS;
}
