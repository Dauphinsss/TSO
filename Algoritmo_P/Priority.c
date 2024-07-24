#include <stdio.h>
#include "cola_P.h"
#include <unistd.h>
#include <pthread.h>
#include "Planificador_Prioritary.h"

int main(){
    Cola cola = {NULL};
    Proceso p1 = {1, 10, 7, 0, 0, 0, 2};
    Proceso p2 = {2, 5, 6, 2, 0, 0, 1};
    Proceso p3 = {3, 15, 5, 5, 0, 0, 3};
    Proceso p4 = {4, 7, 12, 8, 0, 0, 2};
    Proceso p5 = {5, 3, 9, 11, 0, 0, 2};
    
    iniciarEjecucion(&cola);

    agregarProceso(&cola, p1);
    agregarProceso(&cola, p2);
    
    agregarProceso(&cola, p3);
    
    sleep(3);
    agregarProceso(&cola, p4);
    
    sleep(1);
    agregarProceso(&cola, p5);

    sleep(50);

    printf("Proceso\tTiempo Ejecucion\tTiempo Espera\tTiempo Retorno\n");
    Nodo* terminados = obtenerProcesosTerminados();
    while (terminados != NULL) {
        printf("%d\t\t%d\t\t\t%d\t\t%d\n",
               terminados->proceso.pid,
               terminados->proceso.tiempo_ejecucion,
               terminados->proceso.tiempo_espera,
               terminados->proceso.tiempo_retorno);
        Nodo* temp = terminados;
        terminados = terminados->next;
    }

    return 0;
}
