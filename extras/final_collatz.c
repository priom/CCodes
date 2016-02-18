#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 1024
key_t key = 9876;
int shmid;
int *shm;

int collatz (int n) {
	if (n%2 == 0) {
		n = n / 2;
		return n;
	}
	else {
		n = 3 * n + 1;
		return n;
	}
}

int main(int argc, char *argv[]) {
	int i = 0;
	int n = atoi(argv[1]);
	
	if (argc != 2) {
		printf("Sorry, the number of arguments has to be exactly 2!\n");
        exit(0);
	}
	
	if (n < 1) {
		printf("N has to be more than 0!\n");
		exit(0);
	}
	
	// GET a shared memory section
	if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0) {
		perror("shmget");
		exit(0);
	}
	
	// ATTACH it to the process
	if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
		perror("shmat");
		exit(0);
	}
	
  pid_t pid;
	pid = fork();

	if (pid == -1) {
		printf("Sorry, can't fork, Error!\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) {
		// shm[i] = n;
		// printf("%d ", shm[i]);
		while(n != 1) {
			i++;
			n = collatz(n);
			shm[i] = n;
			// printf("%d ", shm[i]);
		}
		printf("Child process Calculated!\n");
		exit(0);
	}
	else {
		wait(NULL);
		shm[i] = n;
		printf("%d ", shm[i]);
		while (shm[i] != 1) {
			i++;
			printf("%d ", shm[i]);
		}
		printf("\n");
		printf("Parent process Printed!\n");
		exit(0);
	}	

	return 0;	
}