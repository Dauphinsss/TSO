#include <stdio.h>

#define MAX_SIZE 100 // Tamaño máximo de la cola

// Estructura para almacenar un proceso
typedef struct {
    int process_id;
    int priority;
} Process;

// Cola de prioridad usando un array
Process priority_queue[MAX_SIZE];
int size = 0; // Número actual de elementos en la cola

// Función para insertar un proceso en la cola de prioridad
void insert(int process_id, int priority) {
    if (size >= MAX_SIZE) {
        printf("La cola de prioridad está llena.\n");
        return;
    }

    int i = size++;
    while (i > 0 && priority_queue[(i - 1) / 2].priority > priority) {
        priority_queue[i] = priority_queue[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    priority_queue[i].process_id = process_id;
    priority_queue[i].priority = priority;
}

// Función para eliminar el proceso con la mayor prioridad (el primero en el array)
void removeHighestPriority() {
    if (size == 0) {
        printf("La cola de prioridad está vacía.\n");
        return;
    }

    printf("Proceso con ID %d eliminado.\n", priority_queue[0].process_id);
    size--;
    if (size == 0) return;

    Process last = priority_queue[size];
    int i = 0;
    int child = 1;

    while (child < size) {
        if (child + 1 < size && priority_queue[child + 1].priority < priority_queue[child].priority) {
            child++;
        }
        if (last.priority <= priority_queue[child].priority) break;
        priority_queue[i] = priority_queue[child];
        i = child;
        child = 2 * i + 1;
    }
    priority_queue[i] = last;
}

// Función para imprimir la cola de prioridad
void printQueue() {
    if (size == 0) {
        printf("La cola de prioridad está vacía.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        printf("Proceso ID: %d, Prioridad: %d\n", priority_queue[i].process_id, priority_queue[i].priority);
    }
}

int main() {
    // Insertar procesos en la cola de prioridad
    insert(1, 3); // Proceso 1 con prioridad 3
    insert(2, 1); // Proceso 2 con prioridad 1
    insert(3, 2); // Proceso 3 con prioridad 2

    // Imprimir la cola de prioridad
    printf("Cola de prioridad:\n");
    printQueue();

    // Eliminar el proceso con mayor prioridad
    removeHighestPriority();

    // Imprimir la cola de prioridad después de eliminar el proceso
    printf("Cola de prioridad después de eliminar el proceso de mayor prioridad:\n");
    printQueue();

    return 0;
}
