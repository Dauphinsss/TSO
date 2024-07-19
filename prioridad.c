#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PROCESSES 10

// Estructura para almacenar la información de un proceso
typedef struct {
    int id;
    int priority;
} Process;

// Función para crear un nuevo proceso
Process createProcess(int id, int priority) {
    Process process;
    process.id = id;
    process.priority = priority;
    return process;
}

// Función para ordenar los procesos por prioridad (menor valor de prioridad primero)
void sortProcesses(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Función que simula la ejecución de un proceso
void* executeProcess(void* arg) {
    Process* process = (Process*)arg;
    printf("Ejecutando proceso %d con prioridad %d\n", process->id, process->priority);
    sleep(1); // Simula el tiempo de ejecución del proceso
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_PROCESSES];
    Process processes[MAX_PROCESSES];

    // Creación de procesos con prioridades aleatorias
    for (int i = 0; i < MAX_PROCESSES; i++) {
        int priority = rand() % 10 + 1; // Prioridad aleatoria entre 1 y 10
        processes[i] = createProcess(i, priority);
        printf("Proceso %d con prioridad %d creado\n", processes[i].id, processes[i].priority);
    }

    // Ordenar los procesos por prioridad
    sortProcesses(processes, MAX_PROCESSES);

    // Ejecución de procesos en orden de prioridad
    for (int i = 0; i < MAX_PROCESSES; i++) {
        pthread_create(&threads[i], NULL, executeProcess, (void*)&processes[i]);
        pthread_join(threads[i], NULL);
    }

    return 0;
}
