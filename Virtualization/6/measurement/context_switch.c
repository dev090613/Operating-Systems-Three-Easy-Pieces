#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int pipe1[2], pipe2[2];
    pipe(pipe1);
    pipe(pipe2);

    char buf[1];
    struct timeval start, end;

    pid_t rc = fork();
    if (rc == -1) {
        perror("fork failed.");
        exit(1);
    } else if (rc == 0) {
        // child process
    } else {
        // parent process
    }
}
