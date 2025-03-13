#include <stdio.h>	// for printf function.
#include <stdlib.h>	// for exit function.
#include <unistd.h>	// for fork function.
#include <sys/types.h>	// for the type pid_t.
#include <sys/wait.h>	// for wait function.

int main() {
	pid_t pid1, pid2;

	// Create the first child
	pid1 = fork();

	if (pid1 < 0) {
		// Fork failed
		perror("Fork failed for the first child.");
		exit(EXIT_FAILURE);
	} else if (pid1 == 0) {
		// First child process
		printf("First fork loop: ");
		for (int i = 1; i <= 50; i++) {
			printf("%d  ", i);
		}
		printf("\n");

		exit(EXIT_SUCCESS); // Exit the first child process
	} else {
		// Parent process
		// Wait for the first child to finish
		wait(0);
		printf("\nFirst child has finished execution.\n");

		// Create the second child
		pid2 = fork();

		if (pid2 < 0) {
			// Fork failed
			perror("Fork failed for the second child\n");
			exit(EXIT_FAILURE);
		} else if (pid2 == 0) {
			// Second child process
			printf("\nSecond fork loop: ");
			for (int i = 51; i <= 100; i++) {
				printf("%d  ", i);
			}
			printf("\n");
			exit(EXIT_SUCCESS); // Exit the second child process
		} else {
			// Parent process
			// Wait for the second child to finish
			wait(0);
			printf("Second child has finished execution.\n");
		}
	}

	printf("Both children have finished execution.\n");
	return 0;
}
