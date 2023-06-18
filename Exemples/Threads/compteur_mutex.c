/*
 * compteurBOOM.c
 *
 * Synchronization problem
 *
 *
 */

#include <error.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* INT_MAX / 2 */
#define NBITER 1000000000

int counter = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *start_routine(void *arg) {
  int i;

  for (i = 0; i < NBITER; i++) {
    pthread_mutex_lock(&mutex);
    counter ++;
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
  int rc;
  pthread_t thread1, thread2;
  
  rc = pthread_create(&thread1, NULL, start_routine, NULL);
  if (rc)
    error(EXIT_FAILURE, rc, "pthread_create");

  rc = pthread_create(&thread2, NULL, start_routine, NULL);
  if (rc)
    error(EXIT_FAILURE, rc, "pthread_create");

  rc = pthread_join(thread1, NULL);
  if (rc)
    error(EXIT_FAILURE, rc, "pthread_join");
  rc = pthread_join(thread2, NULL);
  if (rc)
    error(EXIT_FAILURE, rc, "pthread_join");

  if (counter != 2 * NBITER)
    printf("BOOM! counter = %d\n", counter);
  else
    printf("OK counter = %d\n", counter);

  exit(EXIT_SUCCESS);
}
