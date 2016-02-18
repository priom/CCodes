/* 
 * A Semaphore Example in 3 Parts
 * - Sema.c, Semb.c, Siminit.c
 */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define KEY 1492

int main(int arc, char** argv)
{
  int id;  /* id of the semaphore. */
  
  /* An "array" of one operation to perform on the semaphore. */
  struct sembuf operations[1];

  /* Get the index for the semaphore with external name KEY. */
  if ((id = semget(KEY, 1, 0666)) < 0) {
    /* Semaphore does not exist. */
    fprintf(stderr, "Program sema cannot find semaphore, exiting.\n");
    exit(0);
  }

  /* Do a semaphore V-operation (Increment/Signal) */
  printf("Program sema (PID: %d) about to do a V-operation.\n", getpid());

  /* Set up the sembuf structure */
  /* Which semaphore in the semaphore array? */
  operations[0].sem_num = 0;
  /* Which operation? Add 1 to semaphore value */
  operations[0].sem_op = 1;
  /* Set the flag so we will wait */   
  operations[0].sem_flg = 0;

  if (semop(id, operations, 1) == 0) {
    printf("Successful V-operation by program sema (PID: %d).\n", getpid());
  } else {
    printf("sema: V-operation did not succeed.\n");
    perror("REASON");
  }
}

/*
 * Endnote:
 *   Consider what the V-operation does. If sema is executed 
 *   twice, then semb can execute twice. 
 */ 
