#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <semaphore.h>

#define KEY 1492
	FILE *file1, *file2, *mergedFile;

sem_t s;

void *fthread (void *param);

int main (int argc, char* argv[]) {

	// Open all 3 files for read and write
	file1 = fopen(argv[1], "r");
	file2 = fopen(argv[2], "r");
	mergedFile = fopen(argv[3], "w");

	// Throw error if there aren't 4 arguments
	if (argc != 5) {
		printf("Sorry, you forgot to enter a file!\n");
		exit(0);
	}

	// Throw error if can't open the file
	if ((!file1) || (!file2) || (!mergedFile)) {
		printf("Sorry, file corrupted!\n");
		exit(0);
	}

	pthread_t thread1, thread2;
	sem_init(&s, 0, 1);
	
	
	// while (getline(&readF1, &size, file1) != EOF) {
	// 	printf("File 1: %s", readF1);
	// }
	pthread_create(&thread1, NULL, fthread, NULL);
  	pthread_join(thread1, NULL);
  	sem_wait(&s);
	// while (getline(&readF2, &size, file2) != EOF) {
	// 	printf("File 2: %s", readF2);
	// }
	pthread_create(&thread1, NULL, fthread, NULL);
  	pthread_join(thread2, NULL);

	return 0;

}

void *fthread (void *param) {
	int size = 100;
	char *readF1, *readF2;

	readF1 = (char *) malloc (size + 1);
	readF2 = (char *) malloc (size + 1);

	while (getline(&readF1, &size, file1) != EOF) {
		printf("File 1: %s", readF1);
	}
	sem_post(&s);
	// pthread_exit(0);
	while (getline(&readF2, &size, file2) != EOF) {
		printf("File 2: %s", readF2);
	}
	
	pthread_exit(0);

}
