#ifndef COLA_H
#define COLA_H

typedef struct Proceso {
    int pid;
    int prioridad;
    int tiempo_ejecucion;
    int tiempo_llegada;
    int tiempo_espera;
    int tiempo_retorno;
    int tiempo_restante;
} Proceso;

typedef struct Nodo {
    Proceso proceso;
    struct Nodo* next;
} Nodo;

typedef struct Cola {
    Nodo* cabecera;
} Cola;

Nodo* crearNodo(Proceso proceso);
void insertar(Cola* cola, Proceso proceso);
Proceso eliminar(Cola* cola);

#endif 