#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* hello(void* arg) {
  printf("Hello !\n");
  sleep(1);
  return NULL;
}

int main(int argc, char**argv) {
  pthread_t tid;
  printf("plip\n");

  int rc = pthread_create(&tid, NULL, hello, NULL);
  if(rc) {
    perror("pthread_create failed");
    abort();
  }

  printf("plup\n");
  
  rc = pthread_join(tid, NULL);
  if(rc) {
    perror("pthread_join failed");
    abort();
  }
 
  printf("plop\n");
  
  return 0;
}
