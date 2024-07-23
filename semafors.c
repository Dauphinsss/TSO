//gcc prod_cons.c -pthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TAM 10

int buffer[TAM];
int count = 0;

// se inicializa indicando que el buffer está completamente vacío al principio.

sem_t sem_vacio; 

//sem_lleno se inicializa a 0 indicando que no hay elementos en el buffer.
sem_t sem_lleno;

//mutex se inicializa para proteger el acceso al buffer.
pthread_mutex_t mutex; 

// funcion productor
void* productor(void* param) {
    int item;
    for (int i = 0; i < 20; ++i) {
	//Produce un elemento aleatorio.
        item = rand() % 100; 

	//Espera hasta que haya un espacio vacio en el buffer 
        sem_wait(&sem_vacio); 
	// Bloquea el acceso al buffer
        pthread_mutex_lock(&mutex); 
	// Anade el elemento al buffer y aumenta el contador
        buffer[count++] = item; 
        printf("Produce: %d\n", item);
	// Desbloquea el buffer 
        pthread_mutex_unlock(&mutex); 
	// Senala que hay un nuevo elemento en el buffer
        sem_post(&sem_lleno); 
    }
    return NULL;
}

void* consumidor(void* arg) {
    int item;
    for (int i = 0; i < 20; ++i) {
        // Espera hasta que haya al menos un elemento en el buffer
	sem_wait(&sem_lleno); 
	// Bloquea el acceso al buffer
        pthread_mutex_lock(&mutex); 
	// Extrae el elemento del buffer y decrementa el contador.
        item = buffer[--count]; 
        printf("Consume: %d\n", item);
	// Desbloquea el buffer
        pthread_mutex_unlock(&mutex); 
	// Senala que hay un nuevo espacio vacío en el buffer 
        sem_post(&sem_vacio); 
    }	
    return NULL;
}

int main() {
    pthread_t pp, pc;

    // inicializar semaforos
    sem_init(&sem_vacio, 0, TAM);
    sem_init(&sem_lleno, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    
    pthread_create(&pp, NULL, productor, NULL);
    pthread_create(&pc, NULL, consumidor, NULL);


    pthread_join(pp, NULL);
    pthread_join(pc, NULL);

    // Clean up
    sem_destroy(&sem_vacio);
    sem_destroy(&sem_lleno);
    pthread_mutex_destroy(&mutex);

    return 0;
}
