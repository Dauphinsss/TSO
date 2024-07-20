#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Definimos una constante para la cantidad de procesos
#define cantidad 5

// Definimos una estructura que representa un proceso
typedef struct {
    int id;                  // ID del proceso
    int prioridad;           // Prioridad del proceso
    int tiempo_ejecucion;    // Tiempo de ejecución del proceso
    int tiempo_espera;       // Tiempo de espera del proceso
    int tiempo_retorno;      // Tiempo de retorno del proceso
} Proceso;

// Función para crear un proceso con un ID y una prioridad dados
Proceso crearProceso(int id, int prioridad) {
    Proceso proceso;
    proceso.id = id;
    proceso.prioridad = prioridad;
    // El tiempo de ejecución se asigna aleatoriamente entre 1 y 5
    proceso.tiempo_ejecucion = rand() % 5 + 1;
    proceso.tiempo_espera = 0;
    proceso.tiempo_retorno = 0;
    return proceso;
}

// Función para ordenar los procesos por prioridad en orden descendente
void sortProcesos(Proceso procesos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (procesos[j].prioridad < procesos[j + 1].prioridad) {
                // Intercambiamos los procesos si están fuera de orden
                Proceso temp = procesos[j];
                procesos[j] = procesos[j + 1];
                procesos[j + 1] = temp;
            }
        }
    }
}

// Función para calcular el tiempo de espera de cada proceso
void buscar_tespera(Proceso procesos[], int n) {
    procesos[0].tiempo_espera = 0; // El primer proceso no espera
    for (int i = 1; i < n; i++) {
        // El tiempo de espera es la suma del tiempo de espera y el tiempo de ejecución del proceso anterior
        procesos[i].tiempo_espera = procesos[i - 1].tiempo_espera + procesos[i - 1].tiempo_ejecucion;
    }
}

// Función para calcular el tiempo de retorno de cada proceso
void buscar_tretorno(Proceso procesos[], int n) {
    for (int i = 0; i < n; i++) {
        // El tiempo de retorno es la suma del tiempo de ejecución y el tiempo de espera
        procesos[i].tiempo_retorno = procesos[i].tiempo_ejecucion + procesos[i].tiempo_espera;
    }
}

// Función para imprimir los tiempos de ejecución, espera y retorno de cada proceso
void buscar_prom_tiempo(Proceso procesos[], int n) {
    buscar_tespera(procesos, n);
    buscar_tretorno(procesos, n);

    printf("Proceso\tTiempo Ejecucion\tTiempo Espera\tTiempo Retorno\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t\t%d\t\t%d\n", procesos[i].id, procesos[i].tiempo_ejecucion, procesos[i].tiempo_espera, procesos[i].tiempo_retorno);
    }
}

// Función para simular la ejecución de un proceso
void ejecutarProceso(Proceso proceso) {
    printf("Ejecutando proceso %d con prioridad %d\n", proceso.id, proceso.prioridad);
    // Simulamos la ejecución del proceso con sleep
    sleep(proceso.tiempo_ejecucion);
}

// Función principal
int main() {
    Proceso procesos[cantidad];

    // Creamos los procesos con IDs y prioridades aleatorias
    for (int i = 0; i < cantidad; i++) {
        int prioridad = rand() % 10 + 1; // Prioridad aleatoria entre 1 y 10
        procesos[i] = crearProceso(i + 1, prioridad);
        printf("Proceso %d con prioridad %d y tiempo de ejecucion %d creado\n", procesos[i].id, procesos[i].prioridad, procesos[i].tiempo_ejecucion);
    }

    // Ordenamos los procesos por prioridad
    sortProcesos(procesos, cantidad);

    // Calculamos y mostramos los tiempos de ejecución, espera y retorno
    buscar_prom_tiempo(procesos, cantidad);

    // Ejecutamos cada proceso en orden de prioridad
    for (int i = 0; i < cantidad; i++) {
        ejecutarProceso(procesos[i]);
    }

    return 0;
}
