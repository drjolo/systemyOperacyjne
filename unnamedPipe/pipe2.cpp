#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

void main()
{

    int pfd[2], pfin, status, fd;
    char *c = (char *)malloc(sizeof(char));

    if (pipe(pfd) < 0) {
        printf("Blad: tworzenie pipy\n");
        exit(1);
    }

    close(pfd[1]);
        while (read(pfd[0], c, 1) > 0) {
            printf("%s",c);
        }
        printf("\n");
        close(pfd[0]);
        exit(0);
    }

    close(pfd[0]);
    fd = open("data.txt", O_RDONLY);
    while (read(fd, c, 1) > 0) {
        write(pfd[1], c, 1);
    }
    close(pfd[1]);
    close(pfin);

}
