//Nrimoni Chowdhury
//A00371596

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int n, i;

    //Open and write in file
    FILE *f;
    f = fopen("lab5.log", "w");

    //Convert char n to int
    n = atoi(argv[1]);

    //Throw error if file can't be opened
    if (f == NULL) {
        printf("Error! File can't be opened\n");
    }

    //Throw error if there aren't 2 arguments
    if (argc != 2) {
        printf("Sorry, the number of arguments has to be exactly 2!\n");
        exit(0);
    }

    //Throw error if n out of range
    if ((n < 1) || (n > 64)) {
        printf("Out of range! n has to be in between 0 to 65.\n");
        exit(0);
    }

    pid_t pid[n];

    //Print starting PID till n
    for (i = 1; i <= n; i++) {
        //Error if fork can't happen
        pid[i] = fork();
        if (pid[i] == -1) {
            printf("Sorry, can't fork, Error!\n");
            exit(EXIT_FAILURE);
        }
        else if (pid[i] == 0) {
            pid[i] = getpid();
            printf("PID  %d  Starting\n", pid[i]);
            fprintf(f, "PID  %d  Starting\n", pid[i]);
            sleep(1);
            exit(0);
        }
    }
    //Print ending PID in reverse order
    for (i = n; i >= 1; i--) {
        int process;
        waitpid(pid[i], &process, 0);
        if (process == 0) {
            printf("PID  %d  Ending\n", pid[i]);
            fprintf(f, "PID  %d  Ending\n", pid[i]);
        }
    }
    return 0;
}