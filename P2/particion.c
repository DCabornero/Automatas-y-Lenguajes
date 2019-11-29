#include "particion.h"

struct _SetEstados{
  int* listaBin;
  SetEstados* next;
  int lenAFD;
};

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

  liberarSetEstados(list->ultimoSetEstados);
  aux = list->primerSetEstados;

  if(aux == NULL){
    list->primerSetEstados = set;
    return;
  }

  while(aux->next != NULL){
    aux = aux->next;
  }
  aux->next = set;
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

SetEstados* crearSetEstados(int lenAFD){
  SetEstados* nuevo = NULL;

  nuevo = (SetEstados*) malloc(sizeof(SetEstados));
  if(!nuevo){
    printf("No se ha podido crear el nuevo setEstado\n");
    return NULL;
  }
  nuevo->listaBin = (int*) calloc(lenAFD, sizeof(int));
  nuevo->next = NULL;
  nuevo->lenAFD = lenAFD;
  return nuevo;
}

SetEstados* copiarSetEstados(SetEstados* set){
  SetEstados* new;
  int i;

  new = crearSetEstados(set->lenAFD);
  for(i=0;i<set->lenAFD;i++){
    new->listaBin[i] = set->listaBin[i];
  }

  return new;
}

SetEstados* unionSetEstados(SetEstados* set1, SetEstados* set2){
  int* listaBin1;
  int* listaBin2;
  SetEstados* result;
  int i = 0;

  if(set1->lenAFD != set2->lenAFD){
    printf("SetEstados con longitud distinta no se pueden unir\n");
    return NULL;
  }

  listaBin1 = set1->listaBin;
  listaBin2 = set2->listaBin;

  result = (SetEstados*) malloc(sizeof(SetEstados));
  result->listaBin = (int*) malloc(sizeof(int)*set1->lenAFD);
  result->lenAFD = set1->lenAFD;
  result->next = NULL;

  for(i=0;i<result->lenAFD;i++){
    result->listaBin[i] = listaBin1[i] || listaBin2[i];
  }
  return result;
}

SetEstados* interseccionSetEstados(SetEstados* set1, SetEstados* set2){
  int* listaBin1;
  int* listaBin2;
  SetEstados* result;
  int i = 0;

  if(set1->lenAFD != set2->lenAFD){
    printf("SetEstados con longitud distinta no se pueden intersecar\n");
    return NULL;
  }

  listaBin1 = set1->listaBin;
  listaBin2 = set2->listaBin;

  result = (SetEstados*) malloc(sizeof(SetEstados));
  result->listaBin = (int*) malloc(sizeof(int)*set1->lenAFD);
  result->lenAFD = set1->lenAFD;
  result->next = NULL;

  for(i=0;i<result->lenAFD;i++){
    result->listaBin[i] = listaBin1[i] && listaBin2[i];
  }
  return result;
}

SetEstados* complementarioSetEstados(SetEstados* set){
  int* listaBin;
  SetEstados* result;
  int i = 0;

  listaBin = set->listaBin;

  result = (SetEstados*) malloc(sizeof(SetEstados));
  result->listaBin = (int*) malloc(sizeof(int)*set->lenAFD);
  result->lenAFD = set->lenAFD;
  result->next = NULL;

  for(i=0;i<result->lenAFD;i++){
    result->listaBin[i] = !listaBin[i];
  }
  return result;
}

SetEstados* restaSetEstados(SetEstados* set1, SetEstados* set2){
  int* listaBin1;
  int* listaBin2;
  SetEstados* result;
  int i = 0;

  if(set1->lenAFD != set2->lenAFD){
    printf("SetEstados con longitud distinta no se pueden intersecar\n");
    return NULL;
  }

  listaBin1 = set1->listaBin;
  listaBin2 = set2->listaBin;

  result = (SetEstados*) malloc(sizeof(SetEstados));
  result->listaBin = (int*) malloc(sizeof(int)*set1->lenAFD);
  result->lenAFD = set1->lenAFD;
  result->next = NULL;

  for(i=0;i<result->lenAFD;i++){
    result->listaBin[i] = listaBin1[i] && !listaBin2[i];
  }
  return result;
}

int cardinalSetEstados(SetEstados* set){
  int i = 0;
  int card = 0;
  for(i=0;i<set->lenAFD;i++){
    card += set->listaBin[i];
  }
  return card;
}

void zerosSetEstados(SetEstados* set){
  int i = 0;
  for(i=0;i<set->lenAFD;i++){
    set->listaBin[i] = 0;
  }
  return;
}

void insertSetEstados(SetEstados* set, int index){
  if(index >= set->lenAFD){
    printf("Indice fuera de rango en insercion\n");
    return;
  }
  set->listaBin[index] = 1;
  return;
}

int isInSetEstados(SetEstados* set, int index){
  return set->listaBin[index];
}

void liberarSetEstados(SetEstados* set){
  if(!set){
    return;
  }
  free(set->listaBin);
  free(set);
  return;
}
