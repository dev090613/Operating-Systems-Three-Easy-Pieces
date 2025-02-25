#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main() {
	
	pid_t rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(rc == 0) {
		// child process
		printf("hello\n");

	} else {
		// parent process
		sleep(1);
		printf("goodbye\n");
	}

	return 0;
}
