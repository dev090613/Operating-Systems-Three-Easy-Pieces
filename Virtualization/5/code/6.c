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
			printf("This is child process: %d\n", (int) getpid());
			exit(0);
	} else {
		// parent process
		int status;
		pid_t wait_result = waitpid(rc, &status, 0);
		printf("\nThis is parent process: %d\n", (int) getpid());
		if (wait_result != -1) {
			printf("return value of waitpid: %d\n", wait_result);
			if (WEXITSTATUS(status) == 0)
				printf("maybe, child process exited status with zero: %d\n\n", WEXITSTATUS(status));
		} else {
			perror("waitpid failed in parent process.");
			exit(1);
		}
	}

	return 0;

}
