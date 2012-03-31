#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

int main()
{

    int fd;
    char *c = (char *)malloc(sizeof(char));

    static const char filename[] = "data.txt";
    FILE *file = fopen ( filename, "r" );
    if ( file != NULL )
    {
        char line [ 128 ]; /* or other suitable maximum line size */
        while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
        {
             fputs ( line, stdout ); /* write the line */
        }
        fclose ( file );
    }
    return(0);
}
