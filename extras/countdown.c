/*
 * Tami Meredith
 * Class Example: Message Passing
 */
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>   
#include <string.h>
#include <stdlib.h>
#include <sys/msg.h>

#define FLAGS     0 /* Or use IPC_NOWAIT if asynchronous */
#define MSGTYPE   0 /* Use the oldest message in the queue */

/*
 * Token we pass around
 */
typedef struct {
    int n;
} token;


/* Usage routine */
void usage () {
    fprintf (stderr, "count <numprocs> <max>\n");
    fprintf (stderr, "    numprocs = 2..10\n    max = numprocs..100\n");
    exit(EXIT_FAILURE);
} // end usage ()

/* Standard error routine */
void failure (char *msg) {
    fprintf(stderr, "%s: error %d\n", msg, errno);
    exit(EXIT_FAILURE);
} // end failure ()

/*
 * mainline
 */
int main (int argc, char **argv) {

    pid_t  pid;         /* Process PID */
    int ringPosition;   /* Process position in the ring */
    int *mbox;          /* Mailboxes for each process */
    int rbox, sbox;     /* Index of receive and send boxes */
    token tkn;          /* Token being passed around */
    int start;            /* Max allowed token data value */
    int i;              /* Loop counter etc. */
    int np;             /* Number of processes */

    if (argc < 3) {
        usage();
    } 
    sscanf(argv[1],"%d", &np);
    if ((np < 2) || (np > 10)) {
        usage();
    }
    sscanf(argv[2],"%d", &start);
    if ((start < np) || (start > 100)) {
        usage();
    }
   
    mbox = malloc (np * sizeof (int)); 
    for (i = 0; i < np; i++) {
         mbox[i] = msgget(IPC_PRIVATE, 0600 | IPC_CREAT);
    }
    for (i = 1; i < np; i++) {
        if ((pid = fork()) == -1) {   
            failure ("can't fork()");
        } else if (pid == 0) {
            ringPosition = i;
            break;
        } else {
            /* Parent */
            ringPosition = 0;
        }
    }
    pid = getpid();

    if (ringPosition == 0) {
        rbox = np-1;
        tkn.n = start-1;
        printf("Process %d: integer is %d", pid, start);
        msgsnd(mbox[ringPosition], &tkn, sizeof(tkn), FLAGS); 
        if (tkn.n-np+1 < 0) {
            printf(" Terminating.\n");
            exit(EXIT_SUCCESS);
        } else {
            printf("\n");
        }
    } else {
        rbox = ringPosition - 1;
    }
    sbox = ringPosition;

    while (1) {
        msgrcv(mbox[rbox], &tkn, sizeof(tkn), MSGTYPE, FLAGS);
        printf("Process %d: integer is %d", pid, tkn.n);
        tkn.n--;
        msgsnd(mbox[sbox], &tkn, sizeof(tkn), FLAGS); 
        if (tkn.n-np+1 < 0) {
            break;
        } else {
            printf("\n");
        }
    }
    printf(" Terminating.\n");

    exit(EXIT_SUCCESS);
} // end main ()