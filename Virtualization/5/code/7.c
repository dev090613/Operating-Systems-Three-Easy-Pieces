#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
	
	pid_t rc = fork();
	if (rc == -1) {
		perror("fork failed");
		exit(1);
	} else if(rc == 0) {
		// child process
		if (close(STDOUT_FILENO) == -1) {
			perror("close failed");
			exit(1);
		}
		
		printf("Hello, world.");
		exit(0);
	} else {
		// parent process
		wait(NULL);
		printf("Child process completed.\n");
	}
	
	return 0;
}
