#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	
	pid_t rc = fork();
	if (rc == -1) {
		perror("fork failed.");
		exit(1);
	} else if (rc == 0) {
		char *v[] = { "ls", "-l", NULL };
		char *envp[] = {"PATH=/bin:/bin/ls", "TERM=console", NULL};

		if (execve("/bin/ls", v, envp) == -1) {
			perror("execution failed");
			exit(1);
		}
	} else {
		// parent process
		wait(NULL);
		printf("child process completed.\n");
	}
	
	return 0;
}
