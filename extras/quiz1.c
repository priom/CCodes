/* Quiz 1 Solution, TMM, Oct.2015 */
#include <stdio.h>
#include <string.h>

int main (int argc, char** argv) {

    char text[256];
    printf("Please enter a sentence: ");
    scanf("%[^\n]", text);
    if (strchr(text,'x') != NULL) 
        printf("The sentence you entered contains an x.\n");
    else 
        printf("The sentence you entered does not contain an x.\n");
    return (0);
} /* end main */