#ifndef SETESTADOS_H
#define SETESTADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afnd.h"

typedef struct SetEstados {
  int* listaBin;
  struct SetEstados* next;
  int lenAFD;
} SetEstados;

SetEstados* crearSetEstados(int lenAFD);

SetEstados* copiarSetEstados(SetEstados* set);

SetEstados* unionSetEstados(SetEstados* set1, SetEstados* set2);

SetEstados* interseccionSetEstados(SetEstados* set1, SetEstados* set2);

SetEstados* complementarioSetEstados(SetEstados* set);

SetEstados* restaSetEstados(SetEstados* set1, SetEstados* set2);

int cardinalSetEstados(SetEstados* set);

void zerosSetEstados(SetEstados* set);

void insertSetEstados(SetEstados* set, int index);

int isInSetEstados(SetEstados* set, int index);

void liberarSetEstados(SetEstados* set);

#endif
