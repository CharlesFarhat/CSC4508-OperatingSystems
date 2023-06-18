#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

int n_places=4;
int n_loops = 100;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread_function(void*arg) {
  static _Atomic int nb_threads=0;
  int my_rank = nb_threads++;
  
  for(int i=0; i<n_loops; i++) {
    usleep(100);
    pthread_mutex_lock(&mutex);
    while(n_places == 0) {
      pthread_cond_wait(&cond, &mutex);
    }
    n_places--;
    pthread_mutex_unlock(&mutex);

    printf("%d est dans le parking\n", my_rank);
    usleep(500000);
    printf("%d sort du parking\n", my_rank);

    pthread_mutex_lock(&mutex);
    n_places ++;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main(int argc, char**argv) {
  int nthreads = 20;
  pthread_t tid[nthreads];
  for(int i=0; i<nthreads; i++) {
    pthread_create(&tid[i], NULL, thread_function, NULL);
  }

  for(int i=0; i<nthreads; i++) {
    pthread_join(tid[i], NULL);
  }

  return EXIT_SUCCESS;
}
