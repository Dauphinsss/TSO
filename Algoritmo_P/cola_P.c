#include <stdio.h>
#include <stdlib.h>
#include "cola_P.h"

Nodo* crearNodo(Proceso proceso) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevoNodo) {
        fprintf(stderr, "Error al asignar memoria\n");
        exit(EXIT_FAILURE);
    }
    nuevoNodo->proceso = proceso;
    nuevoNodo->next = NULL;
    return nuevoNodo;
}

void insertar(Cola* cola, Proceso proceso) {
    Nodo* nuevoNodo = crearNodo(proceso);
    if (cola->cabecera == NULL || cola->cabecera->proceso.prioridad > proceso.prioridad) {
        nuevoNodo->next = cola->cabecera;
        cola->cabecera = nuevoNodo;
    } else {
        Nodo* temp = cola->cabecera;
        while (temp->next != NULL && temp->next->proceso.prioridad <= proceso.prioridad) {
            temp = temp->next;
        }
        nuevoNodo->next = temp->next;
        temp->next = nuevoNodo;
    }
}

Proceso eliminar(Cola* cola) {
    if (cola->cabecera == NULL) {
        perror("Cola vacía, no se puede eliminar\n");
        exit(EXIT_FAILURE);
    }
    Nodo* temp = cola->cabecera;
    Proceso proceso = temp->proceso;
    cola->cabecera = cola->cabecera->next;
    free(temp);
    return proceso;
}
