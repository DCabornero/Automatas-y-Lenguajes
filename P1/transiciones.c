#include "transiciones.h"

struct _Transicion{
  int* estadosDestino;
  Transicion* next;
};

struct _Transiciones{
  int numEstados;
  int numSimbolos;
  /*Linked list*/
  Transicion* primeraTransicion;
  Transicion* ultimaTransicion;
};

Transiciones* TransicionesInstancia(AFND* afnd){
  Transiciones* list = NULL;

  list = (Transiciones*) malloc(sizeof(Transiciones));
  if(!list){
    printf("No se ha podido reservar memoria para la tabla de transiciones\n");
    return NULL;
  }

  list->numEstados = 0;
  list->numSimbolos = AFNDNumSimbolos(afnd);
  list->primeraTransicion = NULL;
  list->ultimaTransicion = NULL;

  return list;
}

Transiciones* TransicionesNuevaTransicion(Transiciones *list){
  Transicion* newT = NULL;

  newT = (Transicion*) malloc(sizeof(Transicion));
  if(!newT){
    printf("No se ha podido reservar memoria para la nueva transicion\n");
    return NULL;
  }

  newT->estadosDestino = NULL;
  newT->next = NULL;

  if(list->numEstados == 0){
    list->primeraTransicion = newT;
  }
  else{
    list->ultimaTransicion->next = newT;
  }
  list->ultimaTransicion = newT;
  list->numEstados++;

  return list;
}

Transiciones* TransicionesInsertarTransicion(Transiciones* list, int* transicion, int numEstado){
  Transicion* trans;
  int i;

  if(list->numEstados <= numEstado){
    printf("Se está pidiendo escribir la transicion de un estado inexistente\n");
    return NULL;
  }

  if(numEstado < 0){
    printf("Se ha pedido una posición negativa en la tabla\n");
    return NULL;
  }

  trans = list->primeraTransicion;
  for(i=0;i<numEstado;i++){
    trans = trans->next;
  }

  trans->estadosDestino = transicion;

  return list;
}

int* TransicionesNesima(Transiciones* list, int numEstado){
  Transicion* transicion;
  int i;

  transicion = list->primeraTransicion;
  for(i=0;i<numEstado;i++){
    transicion = transicion->next;
  }

  return transicion->estadosDestino;
}

int TransicionesNumEstados(Transiciones* list){
  return list->numEstados;
}

int TransicionesNumSimbolos(Transiciones* list){
  return list->numSimbolos;
}

void BorrarTransiciones(Transiciones* list){
  Transicion *anterior, *actual;

  actual = list->primeraTransicion;
  while(actual->next != NULL){
    if(actual->estadosDestino){
      free(actual->estadosDestino);
    }
    anterior = actual;
    actual = actual->next;
    free(anterior);
  }
  free(actual);
  free(list);
}
