/*
 * Assignment 1 Parts n' Pieces
 * Tami Meredith
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define CHILDREN 5

/* Global Shared Memory Stuff
   -- Setup before fork, copied by fork, usable by all after fork */
#define SHMSIZE 1024
key_t key = 9876;
int shmid;
char *shm, *s;

int isParent = 1; /* Flag to identify parent and her children */

int childmain(int argc, char **argv) {

    int myPID = getpid();
    /* wait for shared memory to contain "Done" */
    while (strcmp(shm,"Done") != 0) {
        printf("Child %d saw shared memory contain: %s\n", myPID, shm);
        sleep(1);
    }
    printf("Child %d saw shared memory contain: %s. Terminating\n", myPID, shm);
    return(0);
    exit(EXIT_SUCCESS);
}

int main (int argc, char **argv) {

    char c;
    int i;

    /* 1. GET a shared memory section */
    if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    /* 2. ATTACH it to the process */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    /* 3. Put something into the shared memory */
    sprintf(shm, "Working");

    /* 4. CREATE some Children */
    for (i = 0; i < CHILDREN; i++) {
      isParent = fork();
      if (isParent < 0) {
          perror("fork");
          exit(EXIT_FAILURE);
      } else if (isParent == 0) {
          /* CHILDREN don't want to loop as well! */
          return (childmain (argc, argv));
      }
    }
    // Only the parent gets here
    sleep (10);
    sprintf(shm, "Done");
    printf("Parent: Write done. Exiting\n");

    exit(EXIT_SUCCESS);
} // end main ()

