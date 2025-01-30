#define _GNU_SOURCE
#define NUM_ITERATIONS 100000

#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

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

    int pipe1[2], pipe2[2];
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("pipe failed.");
        exit(1);
    }

    char buf[1] = { "A" };
    long start_time, end_time;

    pid_t rc = fork();
    if (rc == -1) {
        perror("fork failed.");
        exit(1);
    }
    // do not include fork() call time
    start_time = get_usecs();
    if (rc == 0) {
        // child process
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            write(pipe1[1], buf, 1);
            read(pipe2[0], buf, 1);
        }
        close(pipe1[1]); // to exclude close() time
        close(pipe2[0]);
        exit(0);
    } else {
        // parent process
        for (int i = 0; i < NUM_ITERATIONS; i++) {
            write(pipe2[1], buf, 1);
            read(pipe1[0], buf, 1);
        }
    }

    end_time = get_usecs();
    double ctx_switch_cost = (double)(end_time - start_time) /\
                             (2 * NUM_ITERATIONS);
    printf("\nAverage cost of context switch is %f\n", ctx_switch_cost);

    // wait after cost measurement
    wait(NULL);
    close(pipe2[1]);
    close(pipe1[0]);
    return 0;
}
