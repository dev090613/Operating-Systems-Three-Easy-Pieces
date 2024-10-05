#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	
	int rc = fork();
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
