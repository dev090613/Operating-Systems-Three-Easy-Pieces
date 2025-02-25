#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
	
	int fd = open("p2.output", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1) {
		fprintf(stderr, "Failed to open file\n");
		exit(1);
	}

	pid_t rc = fork();
	if (rc < 0){
		fprintf(stderr, "Fork failed\n");
		close(fd);
		exit(1);
	} else if (rc == 0) {
		char *message = "This is child process\n";
		write(fd, message, strlen(message));
	} else {
		char *message = "This is parent process\n";
		write(fd, message, strlen(message));
		wait(NULL);
	}

	close(fd);
	return 0;
}
