#ifndef LISTAESTADOS_H
#define LISTAESTADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afnd.h"

typedef struct _ListaEstados ListaEstados;
typedef struct _Estado Estado;

/*
Input: afnd -> autómata del que queremos obtener la lista de estados
Output: instancia vacía de una lista de estados del AFD
*/
ListaEstados* ListaEstadosInstancia(AFND* afnd);

/*
Input: list -> Lista de Estados descubiertos
       estado -> Estado a insertar en la lista
Output: Devuelve la lista, NULL en caso de que haya algún error
CUIDADO: NO COMPRUEBA QUE EL ESTADO ESTÉ DUPLICADO,
ESO LO HACE ListaEstadosExisteEstado
*/
ListaEstados* ListaEstadosInsertarEstado(ListaEstados* list, int* estado);

/*
Input: list -> Lista de Estados descubiertos
       numEstado -> elemento n-ésimo de la lista de estados que se quiere
Output: Estado número numEstado
*/
int* ListaEstadosNumEstado(ListaEstados* list, int numEstado);

/*
Input: list -> Lista de Estados descubiertos
       listaBin-> Estado que se quiere comprobar si está
Output: Si está, devuelve su lugar. -1 en caso contrario
*/
int ListaEstadosExisteEstado(ListaEstados* list, int* listaBin);

/*
Input: list -> Lista de Estados descubiertos
Output: Número de estados descubiertos
*/
int ListaEstadosNumEstados(ListaEstados* list);

/*
Input: list -> Lista de Estados descubiertos
*/
void BorrarEstado(ListaEstados* list);
#endif
