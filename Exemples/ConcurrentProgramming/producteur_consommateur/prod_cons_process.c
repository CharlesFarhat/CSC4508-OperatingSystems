#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

int n_prod=2;
int n_cons=4;
int n_loops = 20;

int my_rank = 0;
int fd[2];

void function_prod() {
  int next_product_id = n_loops*my_rank;
  for(int i=0; i<n_loops; i++) {

    int product_id;
    usleep(100);
    
    product_id = next_product_id++;
    usleep(500000);
    printf("P%d produit %d\n", my_rank, product_id);

    write(fd[1], &product_id, sizeof(product_id));
  }
}


void function_cons() {
  
  for(int i=0; i<n_loops; i++) {
    int product_id;
    usleep(100);

    read(fd[0], &product_id, sizeof(product_id));
    if(product_id<0)
      exit(EXIT_SUCCESS);
    usleep(100000);
    printf("C%d consomme %d\n", my_rank, product_id);
  }
}


void init() {
  pipe(fd);
}

void finalize() {
}

int main(int argc, char**argv) {
  init();

  pid_t pid_prod[n_prod];
  pid_t pid_cons[n_cons];

  for(int i = 0; i< n_prod; i++) {
    my_rank = i;
    pid_prod[i] = fork();
    if(!pid_prod[i]) {
      function_prod();
      exit(EXIT_SUCCESS);
    }
  }

  for(int i = 0; i< n_cons; i++) {
    my_rank = i;
    pid_cons[i] = fork();
    if(!pid_cons[i]) {
      function_cons();
      exit(EXIT_SUCCESS);
    }
  }

  for(int i=0; i<n_prod; i++) {
    waitpid(pid_prod[i], NULL, 0);
  }
  
  for(int i=0; i<n_cons; i++) {
    int n=-1;
    write(fd[1], &n, sizeof(int));
  }
  for(int i=0; i<n_cons; i++) {
    waitpid(pid_cons[i], NULL, 0);
  }

  finalize();
  return EXIT_SUCCESS;
}
