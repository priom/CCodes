//Nrimoni Chowdhury
//A00371596

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>

#define WAITING 1

#define FLAGS   0 /* or use IPC_NOWAIT if asynchronous */
#define MSGTYPE 0 /* use the oldest message in the queue */
typedef struct {
    char data[256];
} msg;

int main(int argc, char **argv) {
// Throw error if there aren't 3 arguments
	if (argc != 3) {
        printf("Sorry, the number of arguments has to be exactly 3!\n");
        exit(0);
    }
    
	int n, s;
	n = atoi(argv[1]);
	s = atoi(argv[2]);


//Throw error if n & s are out of range
	if ((n < 2) || (n > 12) || (s < n) || (s > 100)) {
        printf("Error! N has to be in between 2 to 12.\n");
        printf("S has to be in between N to 100.\n");
        exit(0);
    }

    pid_t  pid[n];
    msg m;
    int i = 0;
    int *mbox = (int*)malloc(n * sizeof(int));

    for (i = 1; i <= s; i++) {
        // Create mailbox array
        mbox[i] = msgget(IPC_PRIVATE, 0600 | IPC_CREAT);
    	pid[i] = fork();
        // Quit if forking failed
        if (pid[i] == -1) {
            printf("Sorry, can't fork, Error!\n");
            exit(EXIT_FAILURE);
        }
        // Print PID
        else if (pid[i] == 0) {
            pid[i] = getpid();
            msgrcv(mbox[i], &m, sizeof(msg), MSGTYPE, FLAGS);
            printf("Process(%d)  %d:  integer is %s\n", i, pid[i], m.data);
//#if WAITING
    wait(pid);
//#endif    
printf("Process(%d)  %d:  integer is %s Terminating.\n", i, pid[i], m.data);
            exit(0);
        }
        else {
            sprintf(m.data, "%d", s);
            msgsnd(mbox[i], &m, sizeof(msg), FLAGS); 
            s--; 
        }
//Wait
//#if WAITING
  //  wait(pid);
//#endif
  //  printf("Process(%d)  %d:  integer is %s Terminating.\n", i, pid[i], m.data);
    }

//Free memory
    free(mbox);
    return 0;
}
