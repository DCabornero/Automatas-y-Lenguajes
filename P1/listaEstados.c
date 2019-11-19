#include "listaEstados.h"

/*//////////////////////////////////////////////////////////////////////*/
int* _AFNDClausuraBin(AFND* afnd, int estado, int numEstados);
/*////////////////////////////////////////////////////////////////////*/

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

  nuevo = (Estado*) malloc(sizeof(Estado));
  if(!nuevo){
    printf("No se ha podido crear el nuevo estado\n");
    return NULL;
  }

  nuevo->listaBin = NULL;
  nuevo->next = NULL;
  list->ultimoEstado->listaBin = estado;
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
  int i, contador = 0;

  estadoActual = list->primerEstado;

  while(estadoActual->listaBin != NULL){
    for(i=0;i<list->lenAFND;i++){
      if(estadoActual->listaBin[i] != listaBin[i]){
        estadoActual = estadoActual->next;
        contador++;
        break;
      }
    }
    if(i == list->lenAFND){
      return contador;
    }
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
