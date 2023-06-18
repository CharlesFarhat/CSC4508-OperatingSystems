#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#define N 200
int n_loops = 1000000;


struct shared_memory {
  int accounts[N];
  pthread_rwlock_t lock;
  _Atomic int nb_read;
  _Atomic int nb_write;
};
struct shared_memory*shm = NULL;



int read_accounts() {
  pthread_rwlock_rdlock(&shm->lock);
  shm->nb_read++;
  int sum = 0;
  for(int i=0; i<N; i++) {
    sum += shm->accounts[i];
  }
  pthread_rwlock_unlock(&shm->lock);
  return sum;
}

void transfer(int src, int dest, int amount) {
  pthread_rwlock_wrlock(&shm->lock);
  shm->nb_write++;
  shm->accounts[dest] += amount;
  shm->accounts[src] -= amount;
  pthread_rwlock_unlock(&shm->lock);
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

void init() {
  int fd = shm_open("/rw", O_CREAT|O_RDWR, 0600);
  if(fd<0) {
    perror("shm_open failed");
    exit(EXIT_FAILURE);
  }

  int ret = ftruncate(fd, sizeof(struct shared_memory));
  if(ret < 0) {
    perror("ftruncate failed");
    exit(EXIT_FAILURE);
  }

  shm = mmap(NULL, sizeof(struct shared_memory), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  if(!shm) {
    perror("mmap failed");
    exit(EXIT_FAILURE);
  }


  pthread_rwlockattr_t rw_attr;
  pthread_rwlockattr_init(&rw_attr);
  pthread_rwlockattr_setpshared(&rw_attr, PTHREAD_PROCESS_SHARED);
  pthread_rwlock_init(&shm->lock, &rw_attr);

  for(int i = 0; i<N; i++) {
    shm->accounts[i] = 0;
  }
  shm->nb_read=0;
  shm->nb_write=0;
}

void finalize() {
  pthread_rwlock_destroy(&shm->lock);

  shm_unlink("/rw");
}


int main(int argc, char**argv) {
  init();

  int n_proc=4;
  pid_t pid[n_proc];

  for(int i=0; i<n_proc; i++) {
    pid[i] = fork();
    if(!pid[i]) {
      thread_function(NULL);
      exit(EXIT_SUCCESS);
    }
  }

  for(int i=0; i<n_proc; i++) {
    waitpid(pid[i], NULL, 0);
  }

  int balance = read_accounts();
  printf("Balance: %d (expected: 0)\n", balance);

  int nb_op = shm->nb_read+shm->nb_write;
  printf("%d operation, including:\n",nb_op);
  printf("\t%d read operations (%f %% )\n", shm->nb_read, 100.*shm->nb_read/nb_op);
  printf("\t%d write operations (%f %% )\n", shm->nb_write, 100.*shm->nb_write/nb_op);

  finalize();
  return EXIT_SUCCESS;
}

