//Nrimoni Chowdhury
//A 00371596

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int main (int argc, char* argv[]) {
    //take input mode from argv
    char *mode = argv[1];

//convert string to octal
    int o = strtol(mode, 0, 8);

//chmod the input file
    chmod(argv[2], o);

//    if (chmod(argv[2], o) < 0) {
//        fprintf(stderr, "%s: error in chmod(%s) - %d (%s)\n",
//                argv[0], mode, errno, strerror(errno));
//        exit(1);
//    }


//throw error if arg less than 3
    if (argc < 3) {
        printf("Sorry, less than 3 args.\n");
    }

    return 0;
}
