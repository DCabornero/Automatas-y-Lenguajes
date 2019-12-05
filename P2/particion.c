#include "particion.h"

struct _Particion{
  int numSetEstados;
  int lenAFD;
  /*Linked list*/
  SetEstados* primerSetEstados;
  SetEstados* ultimoSetEstados;
};


Particion* ParticionInstancia(AFND* afnd){
  Particion* particion = NULL;
  SetEstados* inicial = NULL;

  particion = (Particion*) malloc(sizeof(Particion));

  if(!particion){
    printf("Error al reservar memoria a la Partición\n");
    return NULL;
  }

  inicial = (SetEstados*) malloc(sizeof(SetEstados));

  if(!inicial){
    printf("Error al reservar memoria al setEstado inicial\n");
    return NULL;
  }

  inicial->listaBin = NULL;
  inicial->next = NULL;

  particion->numSetEstados = 0;
  particion->lenAFD = AFNDNumEstados(afnd);
  particion->primerSetEstados = inicial;
  particion->ultimoSetEstados = inicial;

  return particion;
}

Particion* ParticionInsertarListaBin(Particion* list, int* setEstado){
  SetEstados* nuevo = NULL;

  nuevo = (SetEstados*) malloc(sizeof(SetEstados));
  if(!nuevo){
    printf("No se ha podido crear el nuevo setEstado\n");
    return NULL;
  }

  nuevo->listaBin = NULL;
  nuevo->next = NULL;
  list->ultimoSetEstados->listaBin = setEstado;
  list->ultimoSetEstados->next = nuevo;
  list->ultimoSetEstados = nuevo;
  list->numSetEstados ++;

  return list;
}

int* ParticionNesimaListaBin(Particion* list, int numSetEstados){
  int i;
  SetEstados* setEstado;

  if(list->numSetEstados <= numSetEstados){
    return NULL;
  }

  setEstado = list->primerSetEstados;
  for(i=0;i<numSetEstados;i++){
    setEstado = setEstado->next;
  }

  return setEstado->listaBin;
}

int ParticionExisteListaBin(Particion* list, int* listaBin){
  SetEstados* setEstadoActual;
  int i, contador = 0;

  setEstadoActual = list->primerSetEstados;

  while(setEstadoActual->listaBin != NULL){
    for(i=0;i<list->lenAFD;i++){
      if(setEstadoActual->listaBin[i] != listaBin[i]){
        setEstadoActual = setEstadoActual->next;
        contador++;
        break;
      }
    }
    if(i == list->lenAFD){
      return contador;
    }
  }

  return -1;
}

int ParticionNumSetEstados(Particion* list){
  return list->numSetEstados;
}

SetEstados* ParticionPopSetEstados(Particion* list, int index){
  SetEstados* set;
  SetEstados* aux;
  int i;

  if(index >= list->numSetEstados){
    return NULL;
  }

  aux = list->primerSetEstados;
  for(i=0;i<index-1;i++){
    aux = aux->next;
  }

  if(index == 0){
    list->primerSetEstados = aux->next;
    set = aux;
  }
  else{
    set = aux->next;
    aux->next = set->next;
  }

  list->numSetEstados--;
  return set;
}

void ParticionInsertarSetEstados(Particion* list, SetEstados* set){
  SetEstados* aux;

  set->next = list->ultimoSetEstados;

  aux = list->primerSetEstados;

  if(aux->listaBin == NULL){
    list->primerSetEstados = set;
    list->numSetEstados++;
    return;
  }

  while(aux->next->listaBin != NULL){
    aux = aux->next;
  }
  aux->next = set;
  list->numSetEstados++;
}

int isInParticionSetEstados(Particion* list, SetEstados* set){
  return ParticionExisteListaBin(list, set->listaBin);
}


void BorrarParticion(Particion* list){
  SetEstados *anterior, *actual;

  actual = list->primerSetEstados;
  while(actual->listaBin != NULL){
    free(actual->listaBin);
    anterior = actual;
    actual = actual->next;
    free(anterior);
  }
  free(actual);
  free(list);
}
