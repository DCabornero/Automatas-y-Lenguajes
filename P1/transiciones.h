#ifndef TRANSICIONES_H
#define TRANSICIONES_H

#include "listaEstados.h"

typedef struct _Transiciones Transiciones;
typedef struct _Transicion Transicion;

/*
Input: afnd -> autómata del que queremos obtener la lista de transiciones
Output: instancia vacía de una lista de transiciones del AFD
*/
Transiciones* TransicionesInstancia(AFND* afnd);

/*
Input: list -> Lista de transiciones
Output: Lista de transiciones con una nueva transicion
*/
Transiciones* TransicionesNuevaTransicion(Transiciones *list);

/*
Input: list -> Lista de transiciones
       transicion -> Estado a insertar en la lista
       numEstado -> Número del estado del que se quiera especificar la transicion
Output: Devuelve la lista, NULL en caso de que haya algún error
*/
Transiciones* TransicionesInsertarTransicion(Transiciones* list, int* transicion, int numEstado);

/*
Input: list -> Lista de transiciones
       numEstado -> número n cuyo sentido se explica en output
Output: Transicion del estado n-ésimo
*/
int* TransicionesNesima(Transiciones* list, int numEstado);

/*
Input: list -> Lista de transiciones
Output: Número de estados descubiertos
*/
int TransicionesNumEstados(Transiciones* list);

/*
Input: list -> Lista de transiciones
*/
void BorrarTransiciones(Transiciones* list);
#endif
