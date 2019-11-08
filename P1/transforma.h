#ifndef TRANSFORMA_H
#define TRANSFORMA_H

#include <stdio.h>
#include "afnd.h"
#include "transiciones.h"

/*
Input: afnd -> Autómata en el que hacer el cierre lambda
       estado -> Índice del estado al que calcular el cierre lambda
Output: array binario que representa el estado del AFD formado por las transiciones
        lambda posibles del estado suministrado
*/
int* AFNDClausuraLambda(AFND* afnd, int* estado);

/*
Input: afnd -> AFND del que se parte
       estado -> Estado del AFD
       simbolo -> Simbolo con el que se quiere llegar a otro estado del AFD
       numEstados -> Numero de estados del AFND
Output: Dado un estado del AFD definido por la cadena binaria de estados del AFND
por los que está formado, la función devuelve el estado al que llega con un
cierto símbolo
*/
int* AFNDEstadosDestino(AFND* afnd, int* estado, int simbolo, int numEstados);

/*
Input: trans -> tabla de transiciones del AFD
       listaE -> lista de estados del AFD
       afnd -> AFND del que viene el AFD
Output: Dada una tabla de transiciones y otra de estados, genera el AFD
        correspondiente
*/
AFND* AFNDGenerarAFD(AFND* afnd, Transiciones* trans, ListaEstados* listaE);

AFND* AFNDTransforma(AFND* afnd);

#endif
