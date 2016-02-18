/* 
 * Lab 2 Solution
 * Dr. Tami Meredith, Fall 2015
 */

#include <stdio.h>
#include <stdlib.h>

#define debug 0             /* set to 0 to turn debug output off */

/*
 * Utility function for use in qsort
 */
int ascending (const void* a, const void*b) {
    return (*((int *) a) - *((int *) b));
} /* end ascending() */
 
 /*
  * Minimum/first value in a sorted array
  * Fails on empty arrays (n == 0)
  */
float minimum (int *data, int n) {
    /* n*0 just to avoid param not used warning */
    return ((float) data[n*0]);
} /* end minimum () */

/*
 * Maximum/last value in a sorted array
 * Fails on empty arrays (n == 0)
 */
float maximum (int *data, int n) {
    return ((float) data[n-1]);
} /* end maximum () */

/*
 * Average calculated the usual way
 * Fails on empty arrays (n == 0)
 */
float mean (int *data, int n) {
    float sum = 0.0;
    int   i;
    for (i = 0; i < n; i++) {
        sum += (float) data[i];
    }
    return (sum / ((float) n));
} /* end mean () */

/*
  * Median value in a sorted array
  * Fails on empty arrays (n == 0)
  */
float median (int *data, int n) {
    if ((n % 2) == 0) {
        return mean(&data[(n/2)-1],2);
    } else {
        return ((float) data[n/2]);
    }
} /* end median () */

/*
  * First modal value in a sorted array
  * Ignores multi-modal data
  * Fails on empty arrays (n == 0)
  */
float mode (int *data, int n) {

    int mVal = data[0];      /* modal value */
    int mCnt = 1;            /* occurrences of modal value */
    int curVal = mVal;       /* current value being examined */
    int curCnt = mCnt;       /* count of current value */
    int i;
    
    for (i = 1; i < n; i++) {
        if (data[i] == curVal) {
            curCnt++;
        } else {
            if (curCnt > mCnt) {
               mVal = curVal;
               mCnt = curCnt;
            }
            curVal = data[i];
            curCnt = 1;
        }
    }
    return (float) mVal;
} /* end mode () */

int main (int argc, char** argv) {

    char  fname[256];
    FILE  *fp;
    int   n;                /* number of data items */
    int   *data;
    int   i;                /* loop utility variable */

    if (argc > 1) {
        fprintf(stderr, "%s: warning: command line args not supported\n", argv[0]);
    }

    printf("Please enter a file name: ");
    scanf("%s", fname);
#if debug
    printf("Reading from file: %s\n", fname);
#endif

    if ((fp = fopen (fname,"r")) == NULL) {
        fprintf(stderr, "%s: %s: could not open file\n", argv[0], fname);
        return (EXIT_FAILURE);
    }
    if ((fscanf(fp, "%d\n", &n) != 1) || (n < 1)) {
        fprintf(stderr, "%s: error: invalid or missing value count\n", argv[0]);
        return (EXIT_FAILURE);
    }
    
#if debug
    printf("Reading %d values.\n", n);
#endif    
    if ((data = malloc (n * sizeof(int))) == NULL) {
        fprintf(stderr, "%s: error: memory allocation failure\n", argv[0]);
        return (EXIT_FAILURE);
    }
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d\n", &(data[i]));
    }
    qsort(data, (size_t) n, sizeof(int), ascending);
#if debug
    for (i = 0; i < n; i++) {
        printf("Sorted value %d: %d\n", i, data[i]);
    }
#endif

    printf("The minimum value is %1.2f\n", minimum(data, n)); 
    printf("The maximum value is %1.2f\n", maximum(data, n));  
    printf("The mean value is %1.2f\n", mean(data, n));  
    printf("The median value is %1.2f\n", median(data, n)); 
    printf("The modal value is %1.2f\n", mode(data, n));  
    
    return (0);

} /* end main() */
