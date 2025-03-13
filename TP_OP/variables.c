#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Global variable
int n = 1000;

int main() {
	// Local variable
	int m = 1000;
	pid_t pid;

	printf("PARENT before fork: m=%d at address %p, n=%d at address %p\n", 
			m, &m, n, &n);

	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed\n");
		exit(1);
	} else if (pid == 0) {
		// Child process
		printf("CHILD initial: m=%d at address %p, n=%d at address %p\n", 
				m, &m, n, &n);

		// Modify variables in child
		m = 2000;
		n = 2000;

		printf("CHILD after modification: m=%d at address %p, n=%d at address %p\n", 
				m, &m, n, &n);

		exit(0);
	} else {
		// Parent process
		// Wait a bit to ensure child processes first
		sleep(1);

		printf("PARENT before modification: m=%d at address %p, n=%d at address %p\n", 
				m, &m, n, &n);

		// Modify variables in parent
		m = 3000;
		n = 3000;

		printf("PARENT after modification: m=%d at address %p, n=%d at address %p\n", 
				m, &m, n, &n);

		wait(NULL);  // Wait for child to complete
    }
    
    return 0;
}
