#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NTHREAD 4

void* thread(void* args) {
    printf("Hello world !\n");
    return NULL;
}

int main() {

    pthread_t tid[NTHREAD];

    for (int i=0; i < NTHREAD; i++) {
        pthread_create(&tid[i], NULL, thread, NULL);
    }


    for (int i=0; i < NTHREAD; i++) {
        pthread_join(tid[i], NULL);
    }


    return EXIT_SUCCESS;
}