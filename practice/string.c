//
//  string.c
//  
//
//  Created by Priom on 2015-09-14.
//
//

#include <stdio.h>
#include <string.h>
#define LENGTH 80

int main(void) {
    FILE *stream = stdout;
    int i, ch;
    char buffer[LENGTH+1] = "Hello";

    for (i=0; (i<strlen(buffer)) && ((ch=putc(buffer[i], stream)) != EOF); ++i);
    printf("\n");

}
