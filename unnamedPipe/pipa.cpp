#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
	int fd[2];
	if (pipe(fd) == -1){
		perror("Creating pipe");
		exit(1);
	}
	switch(fork()){
		case -1:
			perror("Creating process");
			exit(1);
		case 0:
			// child process
			dup2(fd[1], 1);
			execvp("./pipeOut", argv);
			perror("command pipeOut");
			exit(1);
		default: {
			// parent process
			close(fd[1]);
			dup2(fd[0], 0);
			execlp("tr", "tr", "a-z", "A-Z", 0);
			perror("command tr");
			exit(1);
		}
	}
	return(0);
}

