#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <sys/types.h>

int main() {
	pid_t pid;
	struct tms stTimeInfo;
	char cwd[1024];

	// create a process.
	pid = fork();

	if (pid < 0){
		perror("Fork failed.\n");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		// print info of child process.
		printf("\n----- CHILD PROCESS (PID: %d) -----\n", getpid());
		printf("Child's PID: %d\n", getpid());;
		printf("Child's Parent PID: %d\n", getppid());
		printf("Real User ID: %d\n", getuid());
		printf("Effective user ID: %d\n", geteuid());
		printf("Effective Group ID: %d\n", getegid());


		if (getcwd(cwd, sizeof(cwd)) != NULL){
			printf("Current Working Directory: %s\n", cwd);
		} else
			perror("Error: getcwd() function failed.\n");

		printf("Nice Value: %d\n", nice(0));

		// get time info
		times(&stTimeInfo);
		printf("tms_utime: %ld\n", stTimeInfo.tms_utime);
		printf("tms_stime: %ld\n", stTimeInfo.tms_stime);
		printf("tms_cutime: %ld\n", stTimeInfo.tms_cutime);
		printf("tms_cstime: %ld\n", stTimeInfo.tms_cstime);

		exit(EXIT_SUCCESS);

	} else {
		// Parent process
		wait(NULL);  // Wait for child to complete
	
		printf("\n----- PARENT PROCESS (PID: %d) -----\n", getpid());
		printf("Real User ID: %d\n", getuid());
		printf("Effective User ID: %d\n", geteuid());
		printf("Effective Group ID: %d\n", getegid());

		if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("Current Working Directory: %s\n", cwd);
		} else {
			perror("getcwd() error");
		}

		printf("Nice value: %d\n", nice(0));  // Get nice value without changing it
 
		times(&stTimeInfo);
		printf("tms_utime: %ld\n", stTimeInfo.tms_utime);
		printf("tms_stime: %ld\n", stTimeInfo.tms_stime);
		printf("tms_cutime: %ld\n", stTimeInfo.tms_cutime);
		printf("tms_cstime: %ld\n", stTimeInfo.tms_cstime);
	}

	return 0;
}
