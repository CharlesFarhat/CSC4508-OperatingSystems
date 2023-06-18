#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdatomic.h>
#include <linux/futex.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <errno.h>
#include <assert.h>

#define NITER 1000000
#define NTHREADS 4

struct lock {
  int flag;
};
typedef struct lock lock_t;


static int futex(int *uaddr, int futex_op, int val,
		 const struct timespec *timeout, int *uaddr2, int val3) {
  return syscall(SYS_futex, uaddr, futex_op, val,
		 timeout, uaddr2, val3);
}

void lock(lock_t *l) {  
  while (1) {
    /* Is the futex available? */
    int expected = 1;
    if (atomic_compare_exchange_strong(&l->flag, &expected, 0))
      return;      /* Yes */

    /* Futex is not available; wait */
    int s = futex(&l->flag, FUTEX_WAIT, 0, NULL, NULL, 0);
    if (s == -1 && errno != EAGAIN) {
      perror("futex_wait failed");
      abort();
    }
  }
}

void unlock(lock_t *l) {
  int expected = 0;
  atomic_compare_exchange_strong(&l->flag, &expected, 1);
  int s = futex(&l->flag, FUTEX_WAKE, 1, NULL, NULL, 0);
  if (s  == -1) {
    perror("futex_wake failed");
    abort();
  }
}

void lock_init(lock_t *l) {
  l->flag = 1;
}


lock_t l;
int x;

void* thread_function(void*arg){
  for(int i=0; i<NITER; i++) {
    //    printf("%d\n", i);
    lock(&l);
    x++;
    unlock(&l);
  }
  return NULL;
}

int main(int argc, char**argv) {
  lock_init(&l);

  pthread_t tids[NTHREADS];
  int ret;
  for(int i = 0; i<NTHREADS; i++) {
    ret = pthread_create(&tids[i], NULL, thread_function, NULL);
    assert(ret == 0);
  }
  for(int i = 0; i<NTHREADS; i++) {
    ret = pthread_join(tids[i], NULL);
    assert(ret == 0);
  }

  printf("x = %d\n", x);
  printf("expected: %d\n", NTHREADS*NITER);
  return EXIT_SUCCESS;

}
