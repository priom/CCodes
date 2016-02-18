// Nrimoni Chowdhury
// A00371596
// Date: 5-Oct-2015

#include <stdio.h>
#include <stdlib.h>

// comparator function for qsort()
int comparator(const void * x, const void * y)
{
    return ( *(int*)x - *(int*)y );
}

//mean function
float meanFunc(int values[], int n) {
    float sum = 0.0;
    int j;
    for (j = 0; j < n; j++) {
        sum += values[j];
    }
    float mean = sum/n;
    return mean;
}

//median function
float medianFunc(int values[], int n) {
    int medIndex, xMedian, yMedian;
    float median;
    if (n % 2 != 0) {
        medIndex = n / 2;
        median = values[medIndex];
        return median;
    }
    else {
        xMedian = n/2;
        yMedian = xMedian + 1;
        median = (values[xMedian] + values[yMedian]) / 2.0;
        return median;
    }

    return 0;
}

//mode function
float modeFunc(int values[], int n) {
    int a, b;
    int mode[n];
    float modeCount = 0.0;
    float modeNum=0.0;

    for (a = 0; a < n; a++) {
        mode[values[a]]++;
    }

    for (b = 0; b < n; b++) {
        if (mode[b] > modeCount) {
            modeCount = mode[b];
            modeNum = b;
        }
    }
    return modeNum;
}

//max function
float maxFunc(int values[], int n) {
    float max = values[n-1];
    return max;
}

//min function
float minFunc(int values[]) {
    float min = values[0];
    return min;
}

int main(int argc, char* argv[]) {
    // open file
    FILE *f = fopen(argv[1],"r");

    // Throw an error if file not found
    if (f == NULL) {
        printf("Sorry, file not found.\n");
    }

    // Take the first line which is the count of number of lines
    int n;
    fscanf(f, "%d", &n);

    if (n > 4097) {
        printf("Sorry, file too large, cannot be more than 4097 lines");
    }

    if (n < 2) {
        printf("Sorry, file too short, cannot be less than 2 lines");
    }

    // Store the values from file in array
    int values[n];
    int i;
    for (i = 0; i < n; i++) {
        fscanf(f, "%d", &values[i]);
    }

    // Sort the values in ascending order
    qsort(values, n, sizeof(int), comparator);

    // Calculate the mean
    printf ("Mean = %0.2f\n", meanFunc(values, n));

    // Calculate the median
    printf ("Median = %0.2f\n", medianFunc(values, n));

    // Calculate the mode
    printf("Mode = %0.2f\n", modeFunc(values, n));

    // Find & print min value
    printf ("Min = %0.2f\n", minFunc(values));

    // Find & print max value
    printf ("Max = %0.2f\n", maxFunc(values, n));

    return 0;
}
