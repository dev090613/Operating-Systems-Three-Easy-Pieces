#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int x = 1;
	printf("Initial value: %d\n", x);
	printf("Main process PID: %d\n\n", (int)getpid());
	int rc = fork();
	if (rc < 0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	} else if(rc == 0) {
		x = 2;
		printf("I am child process(PID: %d)\n", (int) getpid());
		printf("value of child process: %i\n\n", x);
	} else {
		x = 3;
		wait(NULL);
		printf("I am parent process(PID: %d)\n", (int) getpid());
		printf("value of parent process: %i\n\n", x);
	}


	return 0;
}
