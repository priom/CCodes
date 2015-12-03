#include "stdio.h"
#include "stdlib.h"

int main()
{
    double f, c;
    int low, up, step;

    low = 0;
    up = 300;
    step = 10;

    f = low;
    printf("Farenheit\tCelsius\n");
    while (f <= up) {
        c = (5 * (f - 32)) / 9;
        printf("%.2f\t\t%.2f\n", f , c);
        f = f + step;
    }
    printf("---------------------\n");
    
}
