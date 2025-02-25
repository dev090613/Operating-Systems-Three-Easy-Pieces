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
        exit(0);
    } else {
        // This is parent process
        int status;
        pid_t wait_result = waitpid(rc, &status, 0);
        printf("\nThis is parent process: %d\n", (int)getpid());
        if (wait_result != -1) {
            printf("return value of waitpid() sytstem call: %d\n", wait_result);
            printf("Child process exited with status(maybe '0'): %d\n\n", WEXITSTATUS(status));
        } else {
            perror("waitpid failed in parent process.");
            exit(1);
        }
    }

    return 0;
}
