#ifndef PLANIFICADOR_PRIORITARY_H
#define PLANIFICADOR_PRIORITARY_H

#include "cola_P.h"

void agregarProceso(Cola* cola, Proceso proceso);
void* ejecutarProcesos(void* arg);
void iniciarEjecucion(Cola* cola);
Nodo* obtenerProcesosTerminados();

#endif