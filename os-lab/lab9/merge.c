//Nrimoni Chowdhury
//A00371596
//Date: Dec 7, 2015
//Merging 2 files

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <semaphore.h>

#define KEY 1492
FILE *file1, *file2, *mergedFile;

void *fthread ();

sem_t s;

int main (int argc, char* argv[]) {
  // Open all 3 files for read and write
  file1 = fopen(argv[1], "r");
  file2 = fopen(argv[2], "r");
  mergedFile = fopen(argv[3], "w");

  // Throw error if there aren't 4 arguments
  if (argc != 4) {
     printf("Sorry, you forgot something!\n");
     exit(0);
  }

  // Throw error if can't open the file
  if ((!file1) || (!file2) || (!mergedFile)) {
     printf("Sorry, file corrupted!\n");
     exit(0);
  }
  
  // Declare pthread
  pthread_t thread1, thread2;
  
  // Iniatize semaphore
  sem_init(&s, 0, 1);

  // Create first thread for file 
  pthread_create(&thread1, NULL, fthread, NULL);
  pthread_join(thread1, NULL);
  sem_wait(&s);

  // Create second thread for file 
  pthread_create(&thread2, NULL, fthread, NULL);
  pthread_join(thread2, NULL);
 
  //Destroy semaphore
  sem_destroy(&s);

  return 0;
}

//Function for reading and printing file
void *fthread () {
  //Declare size
  size_t size = 1024;
  char *readF1, *readF2;

  //Dynamically allocated memory
  readF1 = (char *) malloc (size + 1);
  readF2 = (char *) malloc (size + 1);

  //Read and print each line of file 1
  while (getline(&readF1, &size, file1) != EOF) {
     fprintf(mergedFile, "FILE 1: %s", readF1);
  }

  //Read and print each line of file 2
  while (getline(&readF2, &size, file2) != EOF) {
     fprintf(mergedFile, "FILE 2: %s", readF2);
  }
 
  //Posting sem
  sem_post(&s);
  pthread_exit(0);
    
  //Free malloc memory
  free(readF1);
  free(readF2);

}

