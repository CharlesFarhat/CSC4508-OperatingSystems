
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

#define NITER 1000000
#define NTHREADS 4

struct node {
  int value;
  struct node* next;
};

struct node *stack = NULL;

#ifdef NOT_THREAD_SAFE

/* thread-unsafe version */
void push(int value) {
  struct node* n = malloc(sizeof(struct node));
  n->value = value;
  n->next = stack;
  stack = n;
}

int pop() {
  struct node* n = stack;
  int value = 0;
  if(n) {
    value = n->value;
    stack = n->next;
    free(n);
  }
  return value;
}

#else

/* thread-safe version */
void push(int value) {
  struct node* n = malloc(sizeof(struct node));
  n->value = value;
  n->next = stack;

  int done = 0;
  do {
    done = atomic_compare_exchange_strong(&stack, &n->next, n);
  } while(!done);
}

int pop() {
  int value = 0;
  struct node* old_head = NULL;
  struct node* new_head = NULL;
  int done = 0;

  do {
    /* Warning: this function still suffers a race condition (search for
     * "ABA problem" for more information).
     * Fixing this would be too complicated for this simple example.
     */
    old_head = stack;
    if(old_head)
      new_head = old_head->next;
    done = atomic_compare_exchange_strong(&stack, &old_head, new_head);
  } while (!done);

  if(old_head) {
    value = old_head->value;
    free(old_head);
  }
  return value;
}

#endif	/* NOT_THREAD_SAFE */


_Atomic int sum = 0;
void* thread_function(void* arg) {
  for(int i=0; i<NITER; i++) {
    push(1);
  }

  int value;
  while((value=pop()) != 0) {
    sum+=value;
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
  printf("sum = %d\n", sum);
  return EXIT_SUCCESS;
}
