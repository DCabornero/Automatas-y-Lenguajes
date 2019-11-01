#ifndef LISTAESTADOS_H
#define LISTAESTADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "afnd.h"

typedef struct _LISTAESTADOS ListaEstados;

/*
Input: afnd -> autómata del que queremos obtener la tabla
Output: lista de listas, donde el primer acceso es relativo a cada nuevo estado
        del AFD y el segundo es una tabla binaria que muestra qué estados estamos
        uniendo mediante transiciones lambda
*/
ListaEstados* ListaEstadosNuevo(AFND* afnd);


/*
Input: lista -> lista de estados con la que se quiere trabajar
       estadoD -> número del estado del autómata determinista
       estadoND -> número del estado del autómata no determinista
Output: True si el estado del autómata determinista incluye al estado del autómata
        no determinista
        False en caso contrario
*/
int ListaEstadosRelacionado(ListaEstados* lista, int estadoD, int estadoND);


/*
Input: lista -> lista de estados con la que se quiere trabajar
       estado -> estado del que se quiere obtener el nombre asociado
Output: Devuelve un nombre único asociado al estado del AFD
*/
char* ListaEstadosNombreEstado(ListaEstados* lista, int estado);


/*
Input: lista -> lista de estados con la que se quiere trabajar
Output: Devuelve el número de estados del AFD
*/
int ListaEstadosNumEstados(ListaEstados* lista);

#endif
