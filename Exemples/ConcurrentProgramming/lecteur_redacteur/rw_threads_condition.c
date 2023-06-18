#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

// This program simulates operations on a set of bank accounts
// Two kinds of operations are available:
// - read operation: compute the global balance (ie. the sum of all accounts)
// - write operation: transfer money from one account to another
//
// Here's an example of the program output:
//
// $ ./rw_threads_condition 
// Balance: 0 (expected: 0)
// 3982358 operation, including:
//         3581969 read operations (89.945932 % )
//         400389 write operations (10.054068 % )

#define N 200
int n_loops = 1000000;
int accounts[N];

int nb_read = 0;
int nb_write = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int readers=0;
int writing=0;

/* read all the accounts */
int read_accounts() {
  pthread_mutex_lock(&mutex);
  while(writing)
    pthread_cond_wait(&cond, &mutex);
  readers++;
  pthread_mutex_unlock(&mutex);

  nb_read++;
  int sum = 0;
  for(int i=0; i<N; i++) {
    sum += accounts[i];
  }

  pthread_mutex_lock(&mutex);
  readers--;
  if(!readers) {
    pthread_cond_signal(&cond);
  }
  pthread_mutex_unlock(&mutex);
  return sum;
}

/* transfer amount units from account src to account dest */
void transfer(int src, int dest, int amount) {
  pthread_mutex_lock(&mutex);
  while(writing || readers)
    pthread_cond_wait(&cond, &mutex);
  writing = 1;
  pthread_mutex_unlock(&mutex);

  nb_write++;
  accounts[dest] += amount;
  accounts[src] -= amount;


  pthread_mutex_lock(&mutex);
  writing=0;
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
}

void* thread_function(void*arg) { 
  for(int i=0; i<n_loops; i++) {

    /* randomly perform an operation
     * threshold sets the proportion of read operation.
     * here, 90% of all the operations are read operation
     * and 10% are write operations
     */
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
