#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int N=10000;
int cpt = 1000;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* thread_credit(void*arg) {
  int x;
  for(int i=0; i<N; i++) {
    pthread_mutex_lock(&mutex);
    x = cpt;
    x = x + 10;
    cpt = x;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void* thread_debit(void*arg) {
  int x;
  for(int i=0; i<N; i++) {
    pthread_mutex_lock(&mutex);
    x = cpt;
    x = x - 10;
    cpt = x;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main(int argc, char**argv) {

  pthread_t tid[2];
  pthread_create(&tid[0], NULL, thread_debit, NULL);
  pthread_create(&tid[1], NULL, thread_credit, NULL);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);

  printf("cpt = %d\n", cpt);
  return EXIT_SUCCESS;
}
