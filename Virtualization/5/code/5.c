#include <unistd.h> // fork(), getpid()
#include <sys/wait.h> // wait()
#include <sys/types.h> // pid_t
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    printf("This is main process: %d\n\n", (int)getpid());

    pid_t rc = fork();
    if (rc == -1) {
        perror("fork failed.");
        exit(1);
    } else if (rc == 0) {
        // This is child process
        printf("\nThis is child process: %d\n", (int)getpid());
        int status;
        pid_t wait_result = wait(&status);
        if (wait_result == -1) {
            perror("wait failed in child process.");
            exit(1);
        }
    } else {
        // This is parent process
        int status;
        pid_t wait_result = wait(&status);
        printf("\nThis is parent process: %d\n", (int)getpid());
        if (wait_result != -1) {
            printf("return value of wait() sytstem call: %d\n", wait_result);
            if (WIFEXITED(status)) {
                printf("Child process exited with status: %d\n\n", WEXITSTATUS(status));
            }
        } else {
            perror("wait failed in parent process.");
            exit(1);
        }
    }

    return 0;
}
