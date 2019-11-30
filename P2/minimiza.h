#ifndef MINIMIZA_H
#define MINIMIZA_H

#include <stdio.h>
#include "afnd.h"
#include "particion.h"

AFND* AFNDMinimiza(AFND* afnd);

/*
Input:
  afnd -> afd del que se quieren saber los estados alcanzables
Output: estructura SetEstados que incluye los estados alcanzables
*/
SetEstados* Reachable(AFND* afnd);

/*
Input:
  afnd -> afd al que vamos a quitar ciertos estados
  set -> conjunto de estados que queremos dejar del afd
Output: nuevo afd solo con los estados especificados (y por tanto solo
con las transiciones que involucran a los mismos)
*/
AFND* AFNDQuitarEstados(AFND* afnd, SetEstados* set);

/*
Input:
  afnd -> afd con todos los estados alcanzables
Output: Particion con conjuntos de estados, donde cada conjunto denota
un estado distinguible
*/
Particion* NonDistinguishable(AFND* afnd);

AFND* AFNDFabricaParticion(AFND* afnd, Particion* particion);
/*
Input:
  afnd -> automata del que se quiere saber el destino de la transicion
  inicial -> índice del estado inicial de la transición
  simbolo -> índice del símbolo de la transición
Output: Índice del destino de la transición del afd con origen en 'inicial'
y con simbolo 'simbolo'. En caso de que no exista tal transición, devuelve -1
*/
int AFNDTransicion(AFND* afnd, int inicial, int simbolo);

#endif
