#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

struct shared_memory {
  int n_places;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
};
struct shared_memory*shm = NULL;

int n_loops = 30;
int n_process = 20;
int my_rank = 0;

void function() {  
  for(int i=0; i<n_loops; i++) {
    usleep(100);
    pthread_mutex_lock(&shm->mutex);
    while(shm->n_places == 0) {
      pthread_cond_wait(&shm->cond, &shm->mutex);
    }
    shm->n_places--;
    pthread_mutex_unlock(&shm->mutex);

    printf("%d est dans le parking\n", my_rank);
    usleep(500000);
    printf("%d sort du parking\n", my_rank);

    pthread_mutex_lock(&shm->mutex);
    shm->n_places ++;
    pthread_cond_signal(&shm->cond);
    pthread_mutex_unlock(&shm->mutex);
  }
}

void init_shared_mem() {
  int fd = shm_open("/cohorte", O_CREAT|O_RDWR, 0600);
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

  shm->n_places = 4;
  pthread_mutexattr_t mutex_attr;
  pthread_mutexattr_init(&mutex_attr);
  pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
  pthread_mutex_init(&shm->mutex, &mutex_attr);


  pthread_condattr_t cond_attr;
  pthread_condattr_init(&cond_attr);
  pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);
  pthread_cond_init(&shm->cond, &cond_attr);
}

void finalize_shared_mem() {
  pthread_mutex_destroy(&shm->mutex);
  pthread_cond_destroy(&shm->cond);

  shm_unlink("/cohorte");
}

int main(int argc, char**argv) {
  init_shared_mem();

  pid_t pids[n_process];
  for(int i = 0; i< n_process; i++) {
    my_rank = i;
    pids[i] = fork();
    if(!pids[i]) {
      function();
      exit(EXIT_SUCCESS);
    }
  }

  for(int i=0; i<n_process; i++) {
    waitpid(pids[i], NULL, 0);
  }

  finalize_shared_mem();
  return EXIT_SUCCESS;
}
