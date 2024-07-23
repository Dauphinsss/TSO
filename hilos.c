#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Función que será ejecutada por el hilo 1
void* print_hello(void* arg) {
    for(int i = 0; i < 5; i++) {
        printf("Hello from thread 1\n");
    }
    return NULL;
}

// Función que será ejecutada por el hilo 2
void* print_world(void* arg) {
    for(int i = 0; i < 5; i++) {
        printf("World from thread 2\n");
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Crear hilo 1
    if(pthread_create(&thread1, NULL, print_hello, NULL)) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    // Crear hilo 2
    if(pthread_create(&thread2, NULL, print_world, NULL)) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Esperar a que los hilos terminen
    if(pthread_join(thread1, NULL)) {
        fprintf(stderr, "Error joining thread 1\n");
        return 2;
    }

    if(pthread_join(thread2, NULL)) {
        fprintf(stderr, "Error joining thread 2\n");
        return 2;
    }

    printf("Both threads finished execution\n");

    return 0;
}
