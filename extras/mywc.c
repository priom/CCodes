/* 
 * mywc.c
 * Unix wc command clone
 * Tami Meredith, Fall 2015
 */

/*
 * KNOWN BUG
 * - Does not get word count write on binary files
 * - It is unknown what counts as an inter-word separator
 * - Neither isspace() nor !isascii() match the Ubuntu wc implementation
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS  0
#define FAILURE -1

/*
 *  ANSI C puts the types in the parameter list for a function
 *    e.g.: int main (int argc, char **argv) {
 *  K&R (Kernigan&Ritchie) or Traditional C puts the types after the
 *    parameter list for a function
 *    e.g.: int main (argc, argv) int argc; char **argv; {
 *
 *  Putting the return type on a separate line makes it easy to search
 *    for definitions since the name starts on the left margin
 *    e.g.: "grep ^main head.c"
 * 
 *  Also note that in function calls there is NO space between the 
 *    function name and the open paren, e.g.: write(...) but there is
 *    one space in the definition -- this can also aid searching
 */
int 
main (argc, argv)
    int    argc;
    char **argv;
{
    FILE *fp;
    int  lines = 0, words = 0, chars = 0;
    int  c;
    int  inWord = 0;

    /* Error check the application usage */
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(FAILURE);
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0], argv[1]);
        exit(FAILURE);
    }

    /* Read the file, one character at a time */
    while ((c = fgetc(fp)) != EOF) {
        /* 1. Count characters */
        chars++;
        /* 2. Count words - things with 1+ spaces between
		 * NOTE: Fails on binary files as I cannot reverse engineer the
		 *       criteria for inter-word separators
		 */
        if (isspace(c)) {
          if (inWord == 1) words++;
          inWord = 0;
        } else {
          inWord = 1;
        }
        /* 3. Count lines */
        if (c == '\n') lines++;
    }
  
    /* Report results and cleanup before exiting */
    printf ("%4d %4d %4d %s\n", lines, words, chars, argv[1]);
    fclose (fp);
    return (SUCCESS);
	
}   /* end of main () */

/* end of mywc.c */