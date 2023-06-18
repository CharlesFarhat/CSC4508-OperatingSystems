#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define N 200
int n_loops = 1000000;
int accounts[N];


_Atomic int nb_read = 0;
_Atomic int nb_write = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int read_accounts() {
  pthread_mutex_lock(&mutex);
  nb_read++;
  int sum = 0;
  for(int i=0; i<N; i++) {
    sum += accounts[i];
  }
  pthread_mutex_unlock(&mutex);
  return sum;
}

void transfer(int src, int dest, int amount) {
  pthread_mutex_lock(&mutex);
  nb_write++;
  accounts[dest] += amount;
  accounts[src] -= amount;
  pthread_mutex_unlock(&mutex);
}

void* thread_function(void*arg) {
  for(int i=0; i<n_loops; i++) {

    int threshold = 90;
    int x = rand()%100;
    if(x < threshold) {
      /* read */
      int balance = read_accounts();
      if(balance != 0) {
	fprintf(stderr, "Error : balance = %d !\n", balance);
	abort();
      }
    } else {
      /* write */
      int src = rand()%N;
      int dest = rand()%N;
      int amount = rand()%100;
      transfer(src, dest, amount);
    }
  }
  return NULL;
}

int main(int argc, char**argv) {
  for(int i = 0; i<N; i++) {
    accounts[i] = 0;
  }

  int nthreads=4;
  pthread_t tid[nthreads];

  for(int i=0; i<nthreads; i++) {
    pthread_create(&tid[i], NULL, thread_function, NULL);
  }

  for(int i=0; i<nthreads; i++) {
    pthread_join(tid[i], NULL);
  }

  int balance = read_accounts();
  printf("Balance: %d (expected: 0)\n", balance);

  int nb_op = nb_read+nb_write;
  printf("%d operation, including:\n",nb_op);
  printf("\t%d read operations (%f %% )\n", nb_read, 100.*nb_read/nb_op);
  printf("\t%d write operations (%f %% )\n", nb_write, 100.*nb_write/nb_op);

  return EXIT_SUCCESS;
}
