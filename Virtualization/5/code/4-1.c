#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){

    pid_t rc = fork();
    if (rc == -1) {
        perror("fork failed.");
        exit(1);
    } else if (rc == 0) {
        if (execl("/bin/ls", "/bin/ls", "-l", NULL) == -1) {
            perror("exec failed.");
            exit(1);
        } 
    } else {
        wait(NULL);
        printf("program complete.");
    }

    return 0;
}
