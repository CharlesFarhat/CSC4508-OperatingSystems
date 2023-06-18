#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define N 10

int n_loops = 20;

struct monitor{
  int value;
  pthread_mutex_t mutex;
  pthread_cond_t cond;
};

int infos[N];
int i_depot, i_extrait;
int nb_produits = 0;
struct monitor places_dispo;
struct monitor info_prete;


void* function_prod(void*arg) {
  static _Atomic int nb_threads=0;
  int my_rank = nb_threads++;
  
  for(int i=0; i<n_loops; i++) {
    int cur_indice;
    int product_id;
    usleep(100);
    pthread_mutex_lock(&places_dispo.mutex);
    while(places_dispo.value == 0) {
      pthread_cond_wait(&places_dispo.cond, &places_dispo.mutex);
    }
    places_dispo.value--;
    cur_indice = i_depot++;
    i_depot = i_depot % N;

    product_id = nb_produits++;
    pthread_mutex_unlock(&places_dispo.mutex);

    usleep(500000);
    printf("P%d produit %d dans %d\n", my_rank, product_id, cur_indice);

    pthread_mutex_lock(&info_prete.mutex);
    infos[cur_indice] = product_id;
    info_prete.value ++;
    pthread_cond_signal(&info_prete.cond);
    pthread_mutex_unlock(&info_prete.mutex);
  }

  return NULL;
}


void* function_cons(void*arg) {
  static _Atomic int nb_threads=0;
  int my_rank = nb_threads++;
  
  for(int i=0; i<n_loops; i++) {
    int cur_indice;
    int product_id;
    usleep(100);
    pthread_mutex_lock(&info_prete.mutex);
    while(info_prete.value == 0) {
      pthread_cond_wait(&info_prete.cond, &info_prete.mutex);
    }
    info_prete.value--;
    product_id = infos[i_extrait];
    cur_indice = i_extrait;
    i_extrait = (i_extrait+1) % N;
    pthread_mutex_unlock(&info_prete.mutex);

    usleep(100000);
    printf("C%d consomme %d depuis %d\n", my_rank, product_id, cur_indice);

    pthread_mutex_lock(&places_dispo.mutex);
    places_dispo.value ++;
    pthread_cond_signal(&places_dispo.cond);
    pthread_mutex_unlock(&places_dispo.mutex);
  }
  return NULL;
}

void init_monitor(struct monitor *m, int value) {
  m->value = value;
  pthread_mutex_init(&m->mutex, NULL);
  pthread_cond_init(&m->cond, NULL);
}

int main(int argc, char**argv) {
  init_monitor(&places_dispo, N);
  init_monitor(&info_prete, 0);
  i_depot = 0;
  i_extrait = 0;

  
  int nthreads_prod=2;
  int nthreads_cons=4;
  pthread_t tid_prod[nthreads_prod];
  pthread_t tid_cons[nthreads_cons];

  for(int i=0; i<nthreads_prod; i++) {
    pthread_create(&tid_prod[i], NULL, function_prod, NULL);
  }
  for(int i=0; i<nthreads_cons; i++) {
    pthread_create(&tid_cons[i], NULL, function_cons, NULL);
  }

  for(int i=0; i<nthreads_prod; i++) {
    pthread_join(tid_prod[i], NULL);
  }
  for(int i=0; i<nthreads_cons; i++) {
    pthread_join(tid_cons[i], NULL);
  }

  return EXIT_SUCCESS;
}
