/*
 * Tami Meredith: Pipe example
 */
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>   
#include <string.h>
#include <stdlib.h>

#define BUFSIZE   64
#define READING    0
#define WRITING    1

/* A variation on perror() */
void 
failure (msg) 
	char *msg;
{
    fprintf(stderr, "%s: error %d\n", msg, errno);
    exit(EXIT_FAILURE);
} /* end failure () */

int main (int argc, char **argv) {

    pid_t  pid;
    int    p[2], i, sum = 0;
    char   buf[BUFSIZE];
   
    /* Create pipe BEFORE we fork (so both have it) */
    if (pipe(p) == -1) {  failure ("pipe allocation failure"); } 

    for (i = 0; i < 10; i++) 
	    {
        if ((pid = fork()) == -1) { failure ("can't fork"); }
        if (pid == 0) 
	    {  /* Child process writes */
            sprintf(buf, "%d", getpid());
            write(p[WRITING], buf, strlen(buf)+1);
            exit(EXIT_SUCCESS);
        } else { /* Parent reads */
            read(p[READING], buf, BUFSIZE);
            sscanf(buf,"%d",&pid);
            sum = sum + pid;
        } 
    }
    printf("Average is %f\n", sum/10.0);
    exit(EXIT_SUCCESS);
} /* end main () */

