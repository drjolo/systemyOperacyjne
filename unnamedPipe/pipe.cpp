#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[ ]) {
int i; /* number of this process (starting with 1) */
int childpid; /* indicates process should spawn another */
int nprocs; /* total number of processes in ring */
int fd[2]; /* file descriptors returned by pipe */
int error; /* return value from dup2 call */

/* check command line for a valid number of processes to generate */
if ( (argc != 2) || ((nprocs = atoi (argv[1])) <= 0) ) {
	fprintf (stderr, "Usage: %s nprocs\n", argv[0]);
	exit(1);
}

/* connect std input to std output via a pipe */
if (pipe (fd) == -1) {
	perror("Could not create pipe");
	exit(1);
}
if ((dup2(fd[0], STDIN_FILENO) == -1) || (dup2(fd[1], STDOUT_FILENO) == -1)) {
	perror("Could not dup pipes");
	exit(1);
}
if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
	perror("Could not close extra descriptors");
	exit(1);
}

/* create the remaining processes with their connecting pipes */
for (i = 1; i < nprocs; i++) {
	if (pipe (fd) == -1) {
		fprintf(stderr,"Could not create pipe %d: %s\n", i, strerror(errno));
		exit(1);
	}
	if ((childpid = fork()) == -1) {
		fprintf(stderr, "Could not create child %d: %s\n", i, strerror(errno));
		exit(1);
	}
	if (childpid > 0)
		/* for parent process, reassign stdout */
		error = dup2(fd[1], STDOUT_FILENO);
	else
		error = dup2(fd[0], STDIN_FILENO);
	if (error == -1) {
		fprintf(stderr, "Could not dup pipes for iteration %d: %s\n", i, strerror(errno));
		exit(1);
	}
	if ((close(fd[0]) == -1) || (close(fd[1]) == -1)) {
		fprintf(stderr, "Could not close extra descriptors %d: %s\n", i, strerror(errno));
		exit(1);
	}
	if (childpid)
		break;
}

/* say hello to the world */

fprintf(stderr,"This is process %d with ID %d and parent id %d\n", i, (int)getpid(), (int)getppid());
exit (0);
return (0);
}
/* end of main program here */

