#define _GNU_SOURCE
#define NUM_ITERATIONS 10000

#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fcntl.h> // O_RDONLY
#include <sched.h> // CPU_ZERO, CPU_SET macro


long get_usecs()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000L + tv.tv_usec;
}

int main(int argc, char *argv[]) {
    // CPU binding
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(0, &cpu_set);

    if (sched_setaffinity(0, sizeof(cpu_set), &cpu_set) == -1) {
        perror("sched_setaffinity failed.");
        exit(1);
    }


    long start_time, end_time;
    double timer_cost, system_call_cost;

    // Check precision of timer
    start_time = get_usecs();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        get_usecs();
    }
    end_time = get_usecs();
    timer_cost = (double)(end_time - start_time) / NUM_ITERATIONS;
    printf("\ntimer's overhead: %f micro seconds.\n", timer_cost);

    // Check cost of system call
    int fd = open("/dev/null", O_RDONLY);
    if (fd == -1) {
        perror("open failed.");
        exit(1);
    }

    char buf[1];

    start_time = get_usecs();
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        // read zero byte
        read(fd, buf, 0);
    }
    end_time = get_usecs();
    system_call_cost = (double)(end_time - start_time) / NUM_ITERATIONS;
    system_call_cost -= timer_cost;

    printf("\nAverage system call cost: %f micro seconds.\n", system_call_cost);

    close(fd);

    return 0;
}
