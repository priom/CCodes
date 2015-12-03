#include <stdio.h>
#include <stdlib.h>

int main() {
    int c;
    scanf("%d", &c);

    switch (c)  {
        default:
            printf("This is just a mess …\n");
        case  '\n':
        case '\t':
            printf("c is whitespace\n"); break;
        case '_':
            printf("c is an underscore"); break;
        default :
            printf("c is unspecified\n");
    }

    int i;
    for(i=0; i<10; i++) {
        if((i%10)==0) continue;
        printf("%d is not divisible by 10\n", i);
    }

}
