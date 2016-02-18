/*
 * Tami Meredith
 * Class Example
 */

#define slow 0

#include <stdio.h>   /* printf, stderr, fprintf */
#include <unistd.h>  /* exit, fork */
#include <stdlib.h>  /* exit */
#include <errno.h>   /* errno */
#include <limits.h>  /* INT_MAX */

#define NUMPROCS 20

void wasteTime () {
    float f1 = 3.14, 
          f2 = 19.456;
    int i;
    for (i = 0; i < INT_MAX; i++) {
      f1 += f2;
      f1 *= 2.0;
      f2 *= 0.5;
      f1 *= 0.5;
      f2 *= 2.0;
      f1 -= f2;
    }
    printf("Wasted time to calculate: %f\n", f1);
}

int main(int argc, char **argv) {

    pid_t  pid, me;
    int    i, p;

    for (i = 0; i < NUMPROCS; i++) {
        if ((pid = fork()) == -1) {   
            /* Error has occurred and no fork happened. */
            fprintf(stderr, "can't fork, error %d\n", errno);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process, don't know own pid */
            me = getpid();
            printf("My pid is %d. I am a child.\n", me);
            break;
        } else { 
           /* Parent process, pid is that of child */
           me = getpid();
           printf("My child's pid is %d. I am the parent %d.\n", pid, me);
        }
    }

    printf("I am %d. I am going to waste time.\n", me);
    wasteTime();
    printf("Process %d finished\n", me);
    exit(EXIT_SUCCESS);
} // end main ()
 
