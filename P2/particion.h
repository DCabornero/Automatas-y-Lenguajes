#ifndef PARTICION_H
#define PARTICION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afnd.h"

typedef struct _Particion Particion;
typedef struct _SetEstados SetEstados;

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
Particion* ParticionInsertarListaBin(Particion* list, int* estado);

/*
Input: list -> Lista de Estados descubiertos
       numEstado -> elemento n-ésimo de la lista de estados que se quiere
Output: Estado número numEstado
*/
int* ParticionNesimaListaBin(Particion* list, int numEstado);

/*
Input: list -> Lista de Estados descubiertos
       listaBin-> Estado que se quiere comprobar si está
Output: Si está, devuelve su lugar. -1 en caso contrario
*/
int ParticionExisteListaBin(Particion* list, int* listaBin);

/*
Input: list -> Lista de Estados descubiertos
Output: Número de estados descubiertos
*/
int ParticionNumSetEstados(Particion* list);

/*
Input: list -> particion de la que queremos sacar un conjunto de estados
       index -> posicion en la lista del conjunto de estados
Output: estado que hemos extraído
*/
SetEstados* ParticionPopSetEstados(Particion* list, int index);

/*
Input: list -> partición a la que queremos insertar un conjunto de estados al final
       set -> conjunto de estados a insertar
*/
void ParticionInsertarSetEstados(Particion* list, SetEstados* set);

/*
Input: list-> Partición en la que comprobaremos si el conjunto está o no
       set -> Conjunto que nos preguntamos si está o no
Output: -1 si el conjunto no está. La posición en caso contrario
*/
int isInParticionSetEstados(Particion* list, SetEstados* set);

/*
Input: list -> Lista de Estados descubiertos
*/
void BorrarParticion(Particion* list);


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
