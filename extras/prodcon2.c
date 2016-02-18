/* 
 * prodcon.c: Producer-Consumer Example
 * Using POSIX threads and Semaphores
 * Tami Meredith, Fall 2015
 * Using a fixed capacity buffer, producer creates items for a set
 * number of cycles (i.e., 4 items 5 times). The consumer consumes that
 * number of items for an equal number of cycles.
 */

#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFSIZE 8
#define FULL    0
#define EMPTY   0
#define CYCLES  5
#define ITEMS   4

int buffer[BUFSIZE];
int serialNo  = 5678;

int nextIn  = 0;
int nextOut = 0;

/* Semaphores 
 * can_produce: buffer has space, producer can run 
 * can_consume: buffer has items, consumer can run */
sem_t can_produce;
sem_t can_consume;

void fill_buffer()
{
  int i;
  
  sem_wait(&can_produce);
  for (i = 0; i < ITEMS; i++) {
    printf("Producing item %d and putting it in index %d\n", serialNo, nextIn);
    buffer[nextIn] = serialNo++;
    nextIn = (nextIn + 1) % BUFSIZE;
  }
  fflush(stdout);
  sem_post(&can_consume);
} /* end fill_buffer */

void empty_buffer()
{
  int i;

  sem_wait(&can_consume);
  for (i = 0; i < ITEMS; i++) {
    printf("Consuming item %d from index %d\n", buffer[nextOut], nextOut);
    nextOut = (nextOut + 1) % BUFSIZE;
  }
  fflush(stdout);
  sem_post(&can_produce);
} 

/*
 * Producer thread mainline
 */
void *producer()
{
  int i;
  for(i = 0; i < CYCLES; i++) {
    fill_buffer();
  }
} /* end producer() */

/*
 * Consumer thread mainline
 */
void *consumer()
{
  int i;
  for(i = 0; i < CYCLES; i++) {
    empty_buffer();
  }
} /* end consumer */

/*
 * Program mainline
 */
int 
main(int argc, char** argv)
{
  pthread_t ptid, ctid;

  /* Initialize the semaphores */
  sem_init(&can_produce,0,1);
  sem_init(&can_consume,0,0);

  /* Create producer and consumer threads 
     Note: pthread_create returns 0 on success */
  if(pthread_create(&ptid, NULL, producer, NULL) || 
     pthread_create(&ctid, NULL, consumer, NULL))
  {
    fprintf(stderr, "Fatal Error: cannot create thread.\n");
    exit(1);
  }

  /* Wait for the producer and consumer to finish */
  if(pthread_join(ptid, NULL)) {
    fprintf(stderr, "Fatal error: producer did not rejoin process.\n");
    exit(1);
  }
  if(pthread_join(ctid, NULL)) {
    fprintf(stderr, "Fatal error: consumer did not rejoin process.\n");
    exit(1);
  }

  /* Cleanup */
  sem_destroy(&can_produce);
  sem_destroy(&can_consume);
  pthread_exit(NULL);
  return (1);
  
} /* end main() */
