#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TAMANO_BUFFER 20

int buffer[TAMANO_BUFFER];
int contador = 0;

sem_t vacio;
sem_t lleno;
pthread_mutex_t mutex;

void *productor(void *param) {
    int item;
    while (1) {
        item = rand() % 100;
        sleep(1);

        sem_wait(&vacio);
        pthread_mutex_lock(&mutex);
        buffer[contador++] = item;
        printf("Producido: %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&lleno);
    }
}

void *consumidor(void *param) {
    int item;
    while (1) {
        sem_wait(&lleno);
        pthread_mutex_lock(&mutex);

        item = buffer[--contador];
        printf("Consumido: %d\n", item);

        pthread_mutex_unlock(&mutex);
        sem_post(&vacio);

        sleep(2);
    }
}

int main() {
    pthread_t hilo_productor, hilo_consumidor;

    sem_init(&vacio, 0, TAMANO_BUFFER);
    sem_init(&lleno, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&hilo_productor, NULL, productor, NULL);
    pthread_create(&hilo_consumidor, NULL, consumidor, NULL);
    pthread_join(hilo_productor, NULL);
    pthread_join(hilo_consumidor, NULL);

    sem_destroy(&vacio);
    sem_destroy(&lleno);
    pthread_mutex_destroy(&mutex);

    return 0;
}
