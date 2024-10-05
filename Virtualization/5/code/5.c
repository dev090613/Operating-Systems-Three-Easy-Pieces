#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int main() {
	printf("This is main process: %d\n\n", (int) getpid());
	pid_t rc = fork();
	if (rc == -1) {
		perror("fork failed");
		exit(1);
	} else if (rc == 0) {
		// child process
		pid_t wait_result = wait(&rc);
		if (wait_result == -1) {
			printf("\nThis is child process: %d\n", (int) getpid());
			perror("wait failed in child process. error msg");
			exit(1);
		}
	} else {
		// parent process
		pid_t wait_result = wait(&rc);
		printf("\nThis is parent process: %d\n", (int) getpid());
		if (wait_result != -1) {
			printf("return value of wait system call: %d\n", wait_result);
			if (WEXITSTATUS(rc)) {
				printf("child process exited with status: %d\n\n", WEXITSTATUS(rc));
			}
		} else {
			perror("wait failed in parent process.");
			exit(1);
		}
	}

	return 0;

}
