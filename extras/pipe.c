/*
 * Tami Meredith
 * Class Example: Pipes
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

#define child_nap  0
#define parent_nap 1

void failure (char *msg) {
    fprintf(stderr, "%s: error %d\n", msg, errno);
    exit(EXIT_FAILURE);
} // end failure ()

int main (int argc, char **argv) {

    pid_t  pid;
    int    pout[2], cout[2]; 

    char   buf[BUFSIZE];
   
    sprintf (buf, "Knock, knock!");

    /* Create pipe BEFORE we fork (so both have it) */
    if ((pipe(cout) == -1) || (pipe(pout) == -1)) {
        failure ("pipe allocation failure");
    }
    if ((pid = fork()) == -1) {   
        failure ("can't fork");
    }
    if (pid == 0) {
#if child_nap
        sleep(1);
#endif
        /* Child process writes */
        printf("Child writing writing to pipe: %s\n", buf);
        write(cout[WRITING], buf, strlen(buf)+1);
        close(cout[WRITING]);

        /* Child waits */
        printf("Child awaiting response.\n");

        /* Child reads response */
        read(pout[READING], buf, BUFSIZE);
        close(pout[READING]);
        printf("Child received the response: %s\n", buf);
        printf("Child done. Terminating.\n");
    } else { 
        /* Parent waits */
#if parent_nap
        sleep(1);
#endif
        /* Parent process reads */
        read(cout[READING], buf, BUFSIZE);
        printf("Parent received the message: %s\n", buf);
        close(cout[READING]);
        
        /* Parent responds */
        sprintf(buf, "Who's there?");
        printf ("Parent responding with: %s\n", buf);
        write(pout[WRITING], buf, strlen(buf)+1);
        close(pout[WRITING]);
        printf("Parent done. Terminating.\n");
    }
    fflush(stdout);
    exit(0);
} // end main ()

