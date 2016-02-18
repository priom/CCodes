#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

int i, sum;

void
swap(int *a, int *b){
  int t=*a; *a=*b; *b=t;
}

void
sort(int arr[], int beg, int end){
  int piv, l, r;

  if (end > beg + 1){
  
    piv = arr[beg], l = beg + 1, r = end;
    
    while (l < r){
      if (arr[l] <= piv)
        l++;
      else
        swap(&arr[l], &arr[--r]);
    }
    
    swap(&arr[--l], &arr[beg]);
    
    sort(arr, beg, l);  // Have this in a new thread
    sort(arr, r, end);  // And this too!
  }
}

struct thread_args{
  int size;
  int *array;
};

void *average (void *arg) {
    
  struct thread_args *data = arg;
  
  for(i = 0; i < (data->size); i++){
    sum += data->array[i];
  }
  
  printf("Average: %d\n", (sum/data->size));
  
  pthread_exit(0);
}

void 
*minimum (void *arg) {
    
  struct thread_args *data = arg;
  
  printf("Minimum: %d\n", data->array[0]);
  
  pthread_exit(0);
}

void 
*maximum (void *arg) {
    
  struct thread_args *data = arg;
    
  printf("Maximum: %d\n", data->array[(data->size-1)]);
  
  pthread_exit(0);
}

int 
main (int argc, char **argv) {

  int size = argc - 1;
  int *array = (int *) malloc (size * sizeof(int));
  pthread_t  tid1, tid2, tid3;
  pthread_attr_t attr;

  for(i = 1; i <= size; i++){
    array[i-1] = atoi(argv[i]);
  }
  
  sort(array, 0, size);
  
  struct thread_args args = {size, array};
  
  pthread_attr_init(&attr);
  
  pthread_create(&tid1, &attr, average, &args);
  pthread_create(&tid2, &attr, minimum, &args);
  pthread_create(&tid3, &attr, maximum, &args);
  
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  pthread_join(tid3, NULL);

  free(array);
  
  exit(EXIT_SUCCESS);
} // end main ()

