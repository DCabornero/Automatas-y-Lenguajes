#include "setEstados.h"


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
