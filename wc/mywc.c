#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
//    variables for word, line & characater count
    int chCount = 0;
    int lnCount = 0;
    int wdCount = 0;
    int pos = 0;
    char c;

//    open file
    FILE *f;
    f = fopen(argv[1], "r");

//    error is file not found
    if (f == NULL) {
        printf("Sorry, file not found.\n");
        return -1;
    }
    

    while ((c = fgetc(f)) != EOF) {
//        line count
        if (c == '\n') {
            lnCount++;
        }
//        word count
        if (c == ' ' || c == '\n' || c == '\t') {
            pos = 0;
        }
        else if (pos == 0) {
            pos = 1;
            wdCount++;
        }
//        character count
        chCount++;

    }
//    print the count in wc format
    printf(" %d %d %d %s\n", lnCount, wdCount, chCount, argv[1]);
    return 0;
}
