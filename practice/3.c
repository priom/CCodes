//file: 3.c by Priom

#include "stdio.h"
#include "stdlib.h"

#define LOW  0
#define HIGH 300
#define STEP 20

int main()
{
    int f;

    printf("Farenheit\t\Celsius\n");

    for (f = LOW; f <= HIGH; f = f + STEP)
    {
        printf("%d\t\t%f\n", f, (5.0/9.0)*(f - 32));
    }

}
