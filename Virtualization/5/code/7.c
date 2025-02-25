#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    pid_t rc = fork();
    if (rc == -1) {
        perror("fork failed.");
        exit(1);
    } else if (rc == 0) {
        // child process
        printf("This is...\n ");
        close(STDOUT_FILENO);
        printf("child process.\n");
    } else {
        // parent process
        wait(NULL);
        printf("\nThis is ...\n");
        printf("parent process.\n");
        printf("program completed.\n");
    }

    return 0;
}
