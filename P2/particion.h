#ifndef PARTICION_H
#define PARTICION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afnd.h"

typedef struct _Particion Particion;

/*
Input: afnd -> autómata del que queremos obtener la lista de estados
Output: instancia vacía de una partición de estados del AFD
*/
Particion* ParticionInstancia(AFND* afnd);

/*
Input: list -> Lista de Estados de la partición
       estado -> Estado a insertar en la lista
Output: Devuelve la lista, NULL en caso de que haya algún error
CUIDADO: NO COMPRUEBA QUE EL ESTADO ESTÉ DUPLICADO,
ESO LO HACE ParticionExisteEstado
*/
Particion* ParticionInsertarEstado(Particion* list, int* estado);

/*
Input: list -> Lista de Estados descubiertos
       numEstado -> elemento n-ésimo de la lista de estados que se quiere
Output: Estado número numEstado
*/
int* ParticionNumEstado(Particion* list, int numEstado);

/*
Input: list -> Lista de Estados descubiertos
       listaBin-> Estado que se quiere comprobar si está
Output: Si está, devuelve su lugar. -1 en caso contrario
*/
int ParticionExisteEstado(Particion* list, int* listaBin);

/*
Input: list -> Lista de Estados descubiertos
Output: Número de estados descubiertos
*/
int ParticionNumEstados(Particion* list);

/*
Input: list -> Lista de Estados descubiertos
*/
void BorrarEstado(Particion* list);
#endif
