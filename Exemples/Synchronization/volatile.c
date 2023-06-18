#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#if USE_VOLATILE
volatile int a = 0;
#else
int a = 0;
#endif

void* thread1(void*arg) {
  while(a == 0) ;
  printf("Hello\n");
  return NULL;
}

void* thread2(void*arg) {
  a = 1;
  return NULL;
}

int main(int argc, char**argv) {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, thread1, NULL);
  pthread_create(&t2, NULL, thread2, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  return EXIT_SUCCESS;
}
