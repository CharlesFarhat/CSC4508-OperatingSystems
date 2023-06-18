#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

int N=10000;
struct shared_memory {
  int cpt;
  pthread_mutex_t mutex;
};

struct shared_memory*shm = NULL;
void credit() {
  int x;
  for(int i=0; i<N; i++) {
    pthread_mutex_lock(&shm->mutex);
    x = shm->cpt;
    x = x + 10;
    shm->cpt = x;
    pthread_mutex_unlock(&shm->mutex);
  }
}

void debit() {
  int x;
  for(int i=0; i<N; i++) {
    pthread_mutex_lock(&shm->mutex);
    x = shm->cpt;
    x = x - 10;
    shm->cpt = x;
    pthread_mutex_unlock(&shm->mutex);
  }
}

void init_shared_mem() {
  int fd = shm_open("/mutex", O_CREAT|O_RDWR, 0600);
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

  shm->cpt = 1000;
  pthread_mutexattr_t mutex_attr;
  pthread_mutexattr_init(&mutex_attr);
  pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
  pthread_mutex_init(&shm->mutex, &mutex_attr);
}

void finalize_shared_mem() {
  pthread_mutex_destroy(&shm->mutex);
  shm_unlink("/mutex");
}

int main(int argc, char**argv) {

  init_shared_mem();
  pid_t pid_debit = fork();
  if(!pid_debit) {
    debit();
    exit(0);
  }

  pid_t pid_credit = fork();
  if(!pid_credit) {
    credit();
    exit(0);
  }

  waitpid(pid_debit, NULL, 0);
  waitpid(pid_credit, NULL, 0);

  printf("cpt = %d\n", shm->cpt);
  finalize_shared_mem();
  return EXIT_SUCCESS;
}
