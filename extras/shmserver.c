/*
 * Shared memory example: server.c
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
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    key = 1111; /* Any process with this key can get the shared memory */

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

    /* Write abc...z to the shared memory */
    s = shm;
    for (c = 'a'; c <= 'z'; c++) {
        *s++ = c;
    }
    *s = 0;
    printf("Server: SHM = %s\n", shm);
    printf("Server: Write done, waiting for read confirmation\n");

    /* Wait for someone to change the first character to * */
    while (*shm != '*') {
        sleep(NAPTIME);
    }
    printf("Server: SHM = %s\n", shm);
    printf("Server: Segment changed, terminating\n");

    exit(EXIT_SUCCESS);
} // end main ()

