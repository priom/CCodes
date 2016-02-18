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

#define WAITING 0

#define FLAGS   0 /* or use IPC_NOWAIT if asynchronous */
#define MSGTYPE 0 /* use the oldest message in the queue */
typedef struct {
    char data[256];
} msg;

void failure (char *msg) {
    fprintf(stderr, "%s: error %d\n", msg, errno);
    exit(EXIT_FAILURE);
} // end failure ()

int main (int argc, char **argv) {
    pid_t  pid;
    msg m;
    int mboxID = msgget(IPC_PRIVATE, 0600 | IPC_CREAT);

    if ((pid = fork()) == -1) {   
        failure ("can't fork");
    } else if (pid == 0) {
        /* Child reads from the mailbox */
        msgrcv(mboxID, &m, sizeof(msg), MSGTYPE, FLAGS);
        printf("Child is receiving the message.\n");        
        printf("Child received the message: %s\n", m.data);
        printf("Child done. Terminating.\n");
    } else {
        /* Parent writes to mailbox */
        sprintf (m.data, "Happy Birthday!");
        msgsnd(mboxID, &m, sizeof(msg), FLAGS);
        printf("Parent is sending the message. \n");
        printf("Parent has sent the message: %s\n", m.data);
#if WAITING
        wait(pid);
        sleep(1);
#endif
        printf("Parent done. Terminating.\n");  
    }
    exit(0);
} // end main ()

