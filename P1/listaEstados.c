#include "listaEstados.h"

//////////////////////////////////////////////////////////////////////////////////
int* _AFNDClausuraBin(AFND* afnd, int estado, int numEstados);
//////////////////////////////////////////////////////////////////////////////////

struct _Estado{
  int* listaBin;
  Estado* next;
};

struct _ListaEstados{
  int numEstados;
  int lenAFND;
  /*Linked list*/
  Estado* primerEstado;
  Estado* ultimoEstado;
};


ListaEstados* ListaEstadosInstancia(AFND* afnd){
  ListaEstados* listaEstados = NULL;
  Estado* inicial = NULL;

  listaEstados = (ListaEstados*) malloc(sizeof(ListaEstados));

  if(!listaEstados){
    printf("Error al reservar memoria a la lista de estados\n");
    return NULL;
  }

  inicial = (Estado*) malloc(sizeof(Estado));

  if(!inicial){
    printf("Error al reservar memoria al estado inicial\n");
    return NULL;
  }

  inicial->listaBin = NULL;
  inicial->next = NULL;

  listaEstados->numEstados = 0;
  listaEstados->lenAFND = AFNDNumEstados(afnd);
  listaEstados->primerEstado = inicial;
  listaEstados->ultimoEstado = inicial;

  return listaEstados;
}

ListaEstados* ListaEstadosInsertarEstado(ListaEstados* list, int* estado){
  Estado* nuevo = NULL;

  if(sizeof(estado) != sizeof(int)*list->lenAFND){
    printf("Longitud del estado no válida\n");
    return NULL;
  }

  nuevo = (Estado*) malloc(sizeof(Estado*));
  if(!nuevo){
    printf("No se ha podido crear el nuevo estado\n");
    return NULL;
  }

  nuevo->listaBin = estado;
  nuevo->next = 0;
  list->ultimoEstado->next = nuevo;
  list->ultimoEstado = nuevo;
  list->numEstados ++;

  return list;
}

int* ListaEstadosNumEstado(ListaEstados* list, int numEstado){
  int i;
  Estado* estado;

  if(list->numEstados <= numEstado){
    return NULL;
  }

  estado = list->primerEstado;
  for(i=0;i<numEstado;i++){
    estado = estado->next;
  }

  return estado->listaBin;
}

int ListaEstadosExisteEstado(ListaEstados* list, int* listaBin){
  Estado* estadoActual;
  int i;

  if(sizeof(Estado) != sizeof(int)*list->lenAFND){ //SI ESTO NO FUNCIONA PUES LO SIENTO MUCHO//////////////////////
    return -1;
  }

  estadoActual = list->primerEstado;

  while(estadoActual->listaBin != NULL){
    for(i=0;i<list->lenAFND;i++){
      if(estadoActual->listaBin[i] != listaBin[i]){
        estadoActual = estadoActual->next;
        continue;
      }
    }
    return i;
  }

  return -1;
}

int ListaEstadosNumEstados(ListaEstados* list){
  return list->numEstados;
}

void BorrarEstado(ListaEstados* list){
  Estado *anterior, *actual;

  actual = list->primerEstado;
  while(actual->listaBin != NULL){
    free(actual->listaBin);
    anterior = actual;
    actual = actual->next;
    free(anterior);
  }
  free(actual);
  free(list);
}


//-------------------------FUNCIONES PRIVADAS--------------------------
/*
Devuelve una tabla de longitud el número de estados llena de unos y ceros.
En ella, se marcarán con unos los estados a los que se puede llegar por
transiciones lambda desde el estado indicado en los argumentos.
*/
int* _AFNDClausuraBin(AFND* afnd, int estado, int numEstados){
  int* tablaBin = NULL;
  int i = 0;

  tablaBin = calloc(numEstados,sizeof(int));
  tablaBin[estado] = 1;

  for(i=0;i<numEstados;i++){
    if(i != estado){
      if(AFNDCierreLTransicionIJ(afnd,estado,i)){
        tablaBin[i] = 1;
      }
    }
  }

  return tablaBin;
}
