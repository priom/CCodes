/*
 * pc.c: Producer-Consumer Example
 * with threads and semaphores
 * Tami Meredith
 * compile as: gcc -o pc -Wall -pthread pc.c
 */

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define BUFSIZE 5
#define CYCLES  20

int buf[BUFSIZE],
    items;

sem_t mutex,
      consS,
      prodS;

void *produce(void *arg) {

    int i, next = 0;

    /* Go to sleep until its time to produce */ 
    sem_wait(&prodS);

    for(i=0; i<CYCLES; i++) {

        /* Critical section */
        sem_wait(&mutex);
        if (items < BUFSIZE) {
            printf("producing item %d into slot %d\n", i, next);
            buf[next]=i;
            next = (++next)%BUFSIZE;
            items++;
            sleep(1);  /* slow things down a little */
            sem_post(&mutex);

        } else {
            printf("Buffer full, producer waiting...\n");
            i--;
            sem_post(&mutex);
            /* Wake the consumer up */
            sem_post(&consS);
            /* Go to sleep until the consumer wakes me */ 
            sem_wait(&prodS);
        }

    }
    printf("Finished Producing\n");
    /* Wake the consumer up to empty the buffer */
    sem_post(&consS);
}

void *consume(void *arg)
{
    int i, item, next = 0;

    /* Go to sleep until its my turn */
    sem_wait(&consS);

    for(i=0; i<CYCLES; i++) {
      
        /* Critical Section */
        sem_wait(&mutex);
        if (items > 0) {
            item=buf[next];
            printf("consuming item is %d from slot %d\n", item, next);
            next = (++next)%BUFSIZE;
            items--;
            sleep(1);
            sem_post(&mutex);
        } else {
            printf("Buffer empty, consumer waiting...\n");
            i--;
            sem_post(&mutex);
            /* wake the producer up */
            sem_post(&prodS);
            /* Go to sleep until the producer wakes me */
            sem_wait(&consS);
        }

    }
    printf("Finished Consuming\n");
    /* Producer finished first, no wakeup needed */
}

int main(int argc, char **argv)
{
    pthread_t tid1,tid2;

    /* LOW QUALITY CODE - No error checking! */

    sem_init(&mutex,0,1);
    sem_init(&consS,0,0); /* Start consumer @ 0, blocks consumer */
    sem_init(&prodS,0,1);
    items = 0;

    pthread_create(&tid1,NULL,produce,NULL);
    pthread_create(&tid2,NULL,consume,NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return (0);
}
