
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

#define NITER 1000000
#define NTHREADS 4

volatile int x = 0;

#ifdef NOT_THREAD_SAFE

/* thread-unsafe version */
void inc(volatile int * obj) {
  *obj = (*obj)+1;
}

#else

/* thread-safe version */
void inc(volatile int * obj) {
  atomic_fetch_add(obj, 1);
}

#endif 	/* NOT_THREAD_SAFE */

void* thread_function(void* arg) {
  for(int i=0; i<NITER; i++) {
    inc(&x);
  }
  return NULL;
}

int main(int argc, char**argv) {
  pthread_t tids[NTHREADS];
  for(int i = 0; i<NTHREADS; i++) {
    pthread_create(&tids[i], NULL, thread_function, NULL);
  }
  for(int i = 0; i<NTHREADS; i++) {
    pthread_join(tids[i], NULL);
  }

  printf("x = %d\n", x);
  return EXIT_SUCCESS;
}
