/*
 * Tami Meredith
 * Forking and logging: Lab 5
 * Fall 2015
 */

#include <stdio.h>   /* printf, stderr, fprintf */
#include <unistd.h>  /* exit, fork */
#include <stdlib.h>  /* exit */
#include <errno.h>   /* errno */

int main(int argc, char **argv) {

    FILE  *fp = fopen ("lab3.log","w");
    pid_t  pid;
    int    i, n;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <numprocs>\n", argv[0]);
        exit (EXIT_FAILURE);
    }
    n = atoi(argv[1]);
    printf("Creating chain of %d processes.\n", n);
	
    fprintf(fp, "PID %d Starting\n", getpid());
    fflush(fp);
	
    for (i = 1; i < n; i++) {
        if ((pid = fork()) == -1) {   
            /* Error has occurred and no fork happened. */
            fprintf(stderr, "can't fork, error %d\n", errno);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process, don't know own pid */
            fprintf(fp, "PID %d Starting\n", getpid());
            fflush(fp);
        } else { 
            /* Parent process, pid is that of child */
            wait();
            break;
        }
    }
	
    fprintf(fp, "PID %d Ending\n", getpid());
    fflush(fp);
    exit(EXIT_SUCCESS);
	
} // end main ()

