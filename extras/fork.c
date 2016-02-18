/*
 * Tami Meredith
 * Class Example
 */

#define slow 1

#include <stdio.h>   /* printf, stderr, fprintf */
#include <unistd.h>  /* exit, fork */
#include <stdlib.h>  /* exit */
#include <errno.h>   /* errno */

#define NAPTIME 1
int main(int argc, char **argv) {

    pid_t  pid;
    int    i;
     
    if ((pid = fork()) == -1) {   
        /* Error has occurred and no fork happened. */
        fprintf(stderr, "can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
                                                                        
    if (pid == 0) {
        /* Child process, don't know own pid */
        printf("My pid is %d. I am the child.\n", pid);
        for (i = 1; i < 11; i++) {
            printf("child counting up: %d\n", i);
#if slow
            sleep(NAPTIME);
#endif
        }
        printf("Child done. Terminating.\n");
    } else { 
        /* Parent process, pid is that of child */
        printf("My child's pid is %d. I am the parent.\n", pid);
        sleep(NAPTIME);
        for (i = 10; i > 0; i--) {
            printf("parent counting down: %d\n", i);
#if slow
            sleep(NAPTIME);
#endif
        }
        printf("Parent done. Terminating.\n");
    }
    exit(EXIT_SUCCESS);
} // end main ()

