#ifndef TRANSFORMA_H
#define TRANSFORMA_H

#include <stdio.h>
#include "afnd.h"

/*
Input: afnd -> Autómata en el que hacer el cierre lambda
       estado -> Índice del estado al que calcular el cierre lambda
Output: string que representa el estado del AFD formado por las transiciones
        lambda posibles del estado suministrado
*/
char* AFNDClausuraLambda(AFND* afnd, int estado);

AFND* AFNDTransforma(AFND* afnd);

#endif
