#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>



int main() {

	int fd[2];
	if (pipe(fd) == -1) {
		// pipe failed.
		perror("piping failed.\n");
		exit(1);
	}

	pid_t child1 = fork();
	if (child1 == -1) {
		// fork failed.
		perror("fork child1 failed.\n");
		exit(1);
	} else if(child1 == 0) {
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);

		execlp("ls", "ls", NULL);
		// execlp failed.
		perror("execlp ls failed.");
		exit(1);
	}

	pid_t child2 = fork();
	if (child2 == -1) {
		// fork failed.
		perror("fork child1 failed.\n");
		exit(1);
	} else if(child2 == 0) {
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);

		execlp("wc", "wc", NULL);
		// execlp wc failed.
		perror("execlp wc failed.");
		exit(1);
	}
	// parent process
	close(fd[0]);
	close(fd[1]);

	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);

	return 0;
}
