#include <stdio.h>
#include <stdlib.h>
#include "Planificador_Prioritary.h"
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t cola_mutex = PTHREAD_MUTEX_INITIALIZER;
static Cola terminados = {NULL};

void agregarProceso(Cola* cola, Proceso proceso) {
    proceso.tiempo_restante = proceso.tiempo_ejecucion;
    pthread_mutex_lock(&cola_mutex);
    insertar(cola, proceso);
    pthread_mutex_unlock(&cola_mutex);
    printf("Proceso con PID %d agregado.\n", proceso.pid);
}

void agregarTerminado(Proceso proceso) {
    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    nuevo->proceso = proceso;
    nuevo->next = NULL;
    if (terminados.cabecera == NULL) {
        terminados.cabecera = nuevo;
    } else {
        Nodo* actual = terminados.cabecera;
        while (actual->next != NULL) {
            actual = actual->next;
        }
        actual->next = nuevo;
    }
}

void* ejecutarProcesos(void* arg) {
    Cola* cola = (Cola*) arg;
    static int tiempo_simulado = 0;

    while (1) {
        pthread_mutex_lock(&cola_mutex);
        if (cola->cabecera == NULL) {
            pthread_mutex_unlock(&cola_mutex);
            sleep(1);  // Evitar el uso intensivo de CPU
            continue;
        }
        Proceso proceso = eliminar(cola);
        pthread_mutex_unlock(&cola_mutex);

        // Simulamos la ejecución del proceso
        printf("Ejecutando proceso con PID %d y prioridad %d\n", proceso.pid, proceso.prioridad);
        // Simulamos el tiempo de ejecución
        pthread_mutex_lock(&cola_mutex);
        for (int i = 0; i < proceso.tiempo_ejecucion; i++) {
            sleep(1);
            tiempo_simulado++;
            proceso.tiempo_restante--;   
        }

        proceso.tiempo_retorno = tiempo_simulado - proceso.tiempo_llegada;
        proceso.tiempo_espera = proceso.tiempo_retorno - proceso.tiempo_ejecucion;

        pthread_mutex_unlock(&cola_mutex);

        printf("Proceso con PID %d terminado. Tiempo de retorno: %d, Tiempo de espera: %d\n",
               proceso.pid, proceso.tiempo_retorno, proceso.tiempo_espera);

        // Agregamos el proceso terminado a la lista de terminados
        agregarTerminado(proceso);
    }

    return 0;
}

void iniciarEjecucion(Cola* cola) {
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, ejecutarProcesos, cola);
    pthread_detach(thread_id);
}

Nodo* obtenerProcesosTerminados() {
    pthread_mutex_lock(&cola_mutex);
    Nodo* terminadosList = terminados.cabecera;
    terminados.cabecera = NULL;  // Limpiamos la lista de terminados
    pthread_mutex_unlock(&cola_mutex);
    return terminadosList;
}