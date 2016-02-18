#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

int i, j;

void *prime(void *arg) {
  int flag;
  int value = atoi(arg);
  
  for(i=2; i<value; ++i){      
    flag=0;
    for(j=2; j<=i/2; ++j){        
      if(i%j==0){
        flag=1;
        break;
      }
    }
    if(flag==0){
      printf("%d ",i);
    }
  }
  
  printf("\n");
  
  pthread_exit(0);
}

int main (int argc, char* argv[]) {
	if (argc != 2) {
		printf("Error: Enter a number!\n");
		exit(0);
	}
	
	pthread_t thrd;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	
	pthread_create(&thrd, &attr, prime, argv[1]);
	
	pthread_join(thrd, NULL);

	return 0;
	
}