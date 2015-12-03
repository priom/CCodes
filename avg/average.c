// Assignment 7
// Nrimoni Chowdhury
// A00371596
// Date: 15-10-2015

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 1024
key_t key = 9876;
long int shmid;
long int *shm;

int main (int argc, char* argv[]) {
  char n[11];
  int i = 0;
  int len;
  int buf = 0;
  long int store = 0;
  long int sum = 0;
  double avg;

  pid_t pid;

  // Open file in read mode
  FILE *f;
  f = fopen(argv[1], "r");

  // Throw error if there aren't 2 arguments
  if (argc != 2) {
    printf("Sorry, there are must be exactly 2 arguments\n");
    return -1;
  }

  // Throw error if file not found
  if (!f) {
    printf("Sorry, file not found.\n");
    return -1;
  }

  // GET a shared memory section
  if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0) {
      perror("shmget");
      exit(0);
  }

  // ATTACH it to the process
  if ((shm = shmat(shmid, NULL, 0)) == (long int *) -1) {
      perror("shmat");
      exit(0);
  }

  while (i < 10) {
    pid = fork();
    // Exit program if forking failed
    if (pid == -1) {
      printf("Sorry, PID can't be forked\n");
      exit(0);
    }
    // Child process create successfully
    else if (pid == 0) {
      while (fgets(n, sizeof(n), f)) {
        buf++;
        len = atoi(n);
        store += len;
        if (buf == 100) {
          shm[i] = store;
          store = 0;
          buf = 0;
          fprintf(stdout, "Child %d sum is %lu\n", i, shm[i]);
          fflush(stdout);
          i++;
        }
      }
      exit(0);
    }
    // Parent waitng for child to end and the print average
    else {
      wait(0);
      //summing all 10 processes
      for (i = 0; i < 10; i++) {
        sum += shm[i];
      }
      // Calculate Average of the 10 processes
      avg = sum / 10.00;
      fprintf(stdout, "Average %0.2f\n", avg);
      exit(0);
    }
  }
  // close file after all the operations
  fclose(f);
  return 0;
}
