#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Función que será ejecutada por cada hilo
void* print_message_function(void* ptr) {
    char* message = (char*) ptr;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    const char* message1 = "Hola desde el hilo 1";
    const char* message2 = "Hola desde el hilo 2";

    // Crear hilos
    if (pthread_create(&thread1, NULL, print_message_function, (void*) message1)) {
        fprintf(stderr, "Error creando el hilo 1\n");
        return 1;
    }

    if (pthread_create(&thread2, NULL, print_message_function, (void*) message2)) {
        fprintf(stderr, "Error creando el hilo 2\n");
        return 1;
    }

    // Esperar a que los hilos terminen
    if (pthread_join(thread1, NULL)) {
        fprintf(stderr, "Error uniendo el hilo 1\n");
        return 2;
    }

    if (pthread_join(thread2, NULL)) {
        fprintf(stderr, "Error uniendo el hilo 2\n");
        return 2;
    }

    return 0;
}
