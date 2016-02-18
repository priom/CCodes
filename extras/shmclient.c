/*
 * Shared memory example: client.c
 * Tami Meredith
 */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSIZE 2048
#define NAPTIME 1

int main (int argc, char **argv) {
    int shmid;
    key_t key;
    char *shm, *s;

    key = 1111;

    /* 1. GET shared memory */
    if ((shmid = shmget(key, SHMSIZE, 0666)) < 0) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    /* 2. ATTACH shared memory */ 
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Client: Shared memory is %s\n", shm);
    printf("Client: Read Loop >> ");
    for (s = shm; *s != 0; s++) {
        putchar(*s);
    }
    putchar('\n');

    printf("Client: writing a * then terminating\n");
    *shm = '*';

    exit(EXIT_SUCCESS);
} // end main ()
