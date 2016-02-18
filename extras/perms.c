/* 
 * Lab 3 Solution 
 * Tami Meredith, 2015  
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define debug    0
#define SUCCESS  0
#define FAILURE  1
#define BADUSE   2
#define BADFILE  3
#define BADPERMS 4

char *appname;

void error (char *msg, int code) {
    fprintf(stderr, "%s: Error: %s\nAborting\n", appname, msg);
    exit(code);
} // end error () 

void usage (int code) {
    fprintf(stderr, "Usage: %s <perms> <file>\n", appname);
    exit(code);
} // end usage ()

int main (int argc, char** argv) {

    char *file;
    int mode;
    struct stat sbuf;

    appname = argv[0];
    if (argc != 3) {
        usage(BADUSE);
    }

    file = argv[2];
    if (sscanf(argv[1], "%o", &mode) != 1) {
        error ("Invalid permissions used", BADPERMS);
    }

    if (stat(file, &sbuf) == -1) {
        error("File not found", BADFILE);
    }

    if (chmod(file, mode) == -1) {
        error("Failed to change permissions", FAILURE);
    }

    return(SUCCESS);

} // end main ()

