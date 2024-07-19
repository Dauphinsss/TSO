#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define cantidad 5

typedef struct {
    int id;
    int prioridad;
    int tiempo_ejecucion;  
    int tiempo_espera;
    int tiempo_retorno; 
} Proceso;

Proceso crearProceso(int id, int prioridad) {
    Proceso proceso;
    proceso.id = id;
    proceso.prioridad = prioridad;
    proceso.tiempo_ejecucion = rand() % 5 + 1;
    proceso.tiempo_espera = 0;
    proceso.tiempo_retorno = 0;
    return proceso;
}

void sortProcesos(Proceso procesos[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (procesos[j].prioridad < procesos[j + 1].prioridad) {
                Proceso temp = procesos[j];
                procesos[j] = procesos[j + 1];
                procesos[j + 1] = temp;
            }
        }
    }
}

void buscar_tespera(Proceso procesos[], int n) {
    procesos[0].tiempo_espera = 0;
    for (int i = 1; i < n; i++) {
        procesos[i].tiempo_espera = procesos[i - 1].tiempo_espera + procesos[i - 1].tiempo_ejecucion;
    }
}

void buscar_tretorno(Proceso procesos[], int n) {
    for (int i = 0; i < n; i++) {
        procesos[i].tiempo_retorno = procesos[i].tiempo_ejecucion + procesos[i].tiempo_espera;
    }
}

void buscar_prom_tiempo(Proceso procesos[], int n) {
    buscar_tespera(procesos, n);
    buscar_tretorno(procesos, n);

    printf("Proceso\tTiempo Ejecucion\tTiempo Espera\tTiempo Retorno\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t\t%d\t\t%d\n", procesos[i].id, procesos[i].tiempo_ejecucion, procesos[i].tiempo_espera, procesos[i].tiempo_retorno);
    }
}

void ejecutarProceso(Proceso proceso) {
    printf("Ejecutando proceso %d con prioridad %d\n", proceso.id, proceso.prioridad);
    sleep(proceso.tiempo_ejecucion);
}

int main() {
    Proceso procesos[cantidad];

    for (int i = 0; i < cantidad; i++) {
        int prioridad = rand() % 10 + 1;
        procesos[i] = crearProceso(i + 1, prioridad);
        printf("Proceso %d con prioridad %d y tiempo de ejecucion %d creado\n", procesos[i].id, procesos[i].prioridad, procesos[i].tiempo_ejecucion);
    }
    sortProcesos(procesos, cantidad);
    buscar_prom_tiempo(procesos, cantidad);
    for (int i = 0; i < cantidad; i++) {
        ejecutarProceso(procesos[i]);
    }

    return 0;
}
