//Nrimoni Chowdhury
//A00371596
//Date: 23-11-2015
//Thread Quick Sort

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <pthread.h>

//Function declarations
void swap(int *a, int *b);
void sort(int arr[], int beg, int end);
void *threadsort(void *ptr);

//Struct declaration
struct param {
  int *data;
  int beg;
  int end;
};

//Global Variables
int i, n;

int main (int argc, char* argv[]) {
  //Store the data in dynamically allocated memory
  int *data;
  data = (int *) malloc(33 * sizeof(int));
  int val = 0;

  //Open File
  FILE *f, *wf;
  f = fopen(argv[1], "r");
  wf = fopen(argv[1], "a");

  // Throw error if there aren't 2 arguments
  if (argc != 2) {
    printf("Sorry, there are must be exactly 2 arguments\n");
    return -1;
  }

  // Throw error if file not found
  if (!f) {
    printf("Sorry, file not found.\n");
    return -1;
  }

  //Take first number of the file as size of the array
  fscanf (f, "%d\n", &n);
  while (fscanf(f, "%d\n", &val) != EOF) {
    data[i] = val;
    i++;
  }

  //Struct initialization
  struct param arg = {data, 0, n};
  pthread_t pthread;

  //Create and join pthread
  pthread_create(&pthread, NULL, threadsort, &arg);
  pthread_join(pthread, NULL);
  
  

  //Print sorted list to the screen and file
  printf("Sorted List: ");
  fprintf(wf, "Sorted List: ");
  for (i = 0; i < n; i++){
    printf("%d ", data[i]);
    fprintf(wf, "%d ", data[i]);
  }
  printf("\n");
  //Close the file after finish writing it
  fclose(f);

  //Free the malloc
  free(data);
  return 0;
}

//Swap function
void swap (int *a, int *b)
{
  int t = *a; *a = *b; *b = t;
}

//Quick sort function
void sort (int arr[], int beg, int end)
{
  int piv, l, r;
  pthread_t pthread1, pthread2;
  
  //Compare end to begin
  if (end > beg + 1)
  {
    piv = arr[beg];
    l = beg + 1;
    r = end;
    
    //Compare left side with right side
    while (l < r)
    {
      if (arr[l] <= piv)
        l++;
      else
        swap(&arr[l], &arr[--r]);
    }
    
    //Swap left side with right side
    swap(&arr[--l], &arr[beg]);

    //Create and join pthread1
    struct param arg1 = {arr, beg, l};
    pthread_create(&pthread1, NULL, threadsort, &arg1);
    pthread_join(pthread1, NULL);

    //Create and join pthread2
    struct param arg2 = {arr, r, end};
    pthread_create(&pthread2, NULL, threadsort, &arg2);
    pthread_join(pthread2, NULL);
  }
}

//Thread sort function
void *threadsort (void *ptr) {
  struct param *store = ptr;
  sort(store->data, store->beg, store->end);
  pthread_exit(0);
}
