/*
 * Lab 7, Fall 2015
 * Tami Meredith
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define CHILDREN 10 

/* Global Shared Memory Stuff
   -- Setup before fork, copied by fork, usable by all after fork */
#define SHMSIZE (CHILDREN*sizeof(long))
key_t key = 9286;
int shmid;
char *shm, *s;
long *values;

int isParent = 1; /* Flag to identify parent and her children */

int childmain(int n, char *fname) {
    int i, x;
    long sum = n;
    FILE *fp = fopen(fname,"r");
    fseek (fp, 1000*n, SEEK_SET);
    for (i = 0; i < 100; i++) {
        fscanf(fp,"%d\n",&x);
        sum += x;
    } 
    values[n] = sum;
    printf("Child %d sum is %ld\n", n, sum);
    exit(EXIT_SUCCESS);
}

int main (int argc, char **argv) {

    char c;
    int i;
    pid_t pids[CHILDREN];
    long sum;

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
    values = (long *) shm;
    for (i = 0; i < CHILDREN; i++) values[i] = 0;

    /* 4. CREATE some Children */
    for (i = 0; i < CHILDREN; i++) {
      isParent = fork();
      pids[i] = isParent;
      if (isParent < 0) {
          perror("fork");
          exit(EXIT_FAILURE);
      } else if (isParent == 0) {
          /* CHILDREN don't want to loop as well! */
          return (childmain (i, argv[1]));
      }
    }
   
    sum = 0; 
    for (i = 0; i < CHILDREN; i++) {
      wait(pids[i]);
      sum += values[i];
    } 
    sprintf(shm, "Done");
    printf("Average %f\n", ((double)sum)/CHILDREN);

    exit(EXIT_SUCCESS);
} // end main ()

