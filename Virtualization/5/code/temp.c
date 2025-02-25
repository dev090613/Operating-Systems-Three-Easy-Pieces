#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

    int fd[2];
    pid_t pid1, pid2;

    if (pipe(fd) == -1) {
        perror("pipe failed.");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork failed.");
        close(fd[0]);
        close(fd[1]);
        exit(1);
    } else if (pid1 == 0) {
        // child process
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1) {
            perror("dup2 failed");
            close(fd[1]);
            exit(1);
        }
        close(fd[1]);
        
        execlp("ls", "ls", NULL);
        perror("execlp ls failed");
        exit(1);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("fork failed.");
        close(fd[0]);
        close(fd[1]);
        exit(1);
    } else if (pid2 == 0) {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1) {
            perror("dup2 failed.");
            close(fd[0]);
            exit(1);
        }
        close(fd[0]);

        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc failed.");
        exit(1);
    }
    
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
