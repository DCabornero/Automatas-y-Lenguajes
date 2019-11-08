#include "transforma.h"

#define STRLEN 256

///////////////////////////////////////////////////////////////////////////////
int* _AFNDClausuraBin(AFND* afnd, int estado, int numEstados);
char* _AFNDBinAString(AFND* afnd, int* tablaBin, int numEstados);
int _AFNDTipoEstado(AFND* afnd, ListaEstados* listaE, int numEstado);
int* _AFNDMergeEstados(int* tablaBin, int* tablaBinAux, int tam);
///////////////////////////////////////////////////////////////////////////////

int* AFNDClausuraLambda(AFND* afnd, int* estado){
  int numEstados, i;
  int *tablaBin, *tablaBinAux;

  numEstados = AFNDNumEstados(afnd);
  tablaBin = (int*) calloc(numEstados,sizeof(int));

  //Junta las clausuras de cada estado del AFND al que pertenece este estado
  for(i=0;i<numEstados;i++){
    if(estado[i] == 1){
      tablaBinAux = _AFNDClausuraBin(afnd, i, numEstados);
      tablaBin = _AFNDMergeEstados(tablaBin, tablaBinAux, numEstados);
    }
  }
  return tablaBin;
}

int* AFNDEstadosDestino(AFND* afnd, int* estado, int simbolo, int numEstados){
  int i,j;
  int* destino;

  destino = (int*) calloc(numEstados,sizeof(int));
  for(i=0;i<numEstados;i++){
    for(j=0;j<numEstados;j++){
      if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, estado[i], simbolo, estado[j])){
        destino[j] = 1;
      }
    }
  }
  return destino;
}

AFND* AFNDGenerarAFD(AFND* afnd, Transiciones* trans, ListaEstados* listaE){
  AFND* afd;
  char* nameEstado;
  char **tablaNames, **tablaSimbolos;
  int *estadoActual, *transicionActual;
  int numSimbolos, numEstados, tipoEstado;
  int i,j;

  numEstados = ListaEstadosNumEstados(listaE);
  numSimbolos = TransicionesNumSimbolos(trans);
  tablaSimbolos = (char**)malloc(numSimbolos*sizeof(char*));
  tablaNames = (char**)malloc(numEstados*sizeof(char*));
  //Creamos el AFD
  afd = AFNDNuevo("afd", numEstados, numSimbolos);

  //Insertamos sus símbolos
  for(i=0;i<numSimbolos;i++){
    tablaSimbolos[i] = AFNDSimboloEn(afnd, i);
    AFNDInsertaSimbolo(afd,tablaSimbolos[i]);
  }

  //Insertamos sus estados
  for(i=0;i<numEstados;i++){
    estadoActual = ListaEstadosNumEstado(listaE, i);
    nameEstado = _AFNDBinAString(afnd, estadoActual, AFNDNumEstados(afnd));
    tablaNames[i] = nameEstado;
    tipoEstado = _AFNDTipoEstado(afnd, listaE, i);
    AFNDInsertaEstado(afd, nameEstado, tipoEstado);
  }

  //Insertamos las transiciones
  for(i=0;i<numEstados;i++){
    transicionActual = TransicionesNesima(trans, i);
    for(j=0;i<numSimbolos;j++){
        AFNDInsertaTransicion(afd, tablaNames[i], tablaSimbolos[j], tablaNames[transicionActual[j]]);
    }
  }

  return afd;
}

AFND* AFNDTransforma(AFND* afnd){
  AFND* afd;
  ListaEstados* listaEstados;
  Transiciones* transiciones;
  int i,j;
  int numSimbolos;
  int index;
  int* estadoActual; //Estado que se está explorando
  int* estadoSiguiente; //Estado destino del estado actual para el simbolo actual
  int* transicionActual;  //Tabla de transiciones para un cierto estado

  listaEstados = ListaEstadosInstancia(afnd);
  transiciones = TransicionesInstancia(afnd);
  numSimbolos = AFNDNumSimbolos(afnd);

  //Estado inicial
  estadoActual = (int*) calloc(AFNDNumEstados(afnd), sizeof(int));
  estadoActual[AFNDIndiceEstadoInicial(afnd)] = 1;
  estadoActual = AFNDClausuraLambda(afnd, estadoActual);
  listaEstados = ListaEstadosInsertarEstado(listaEstados, estadoActual);
  transiciones = TransicionesNuevaTransicion(transiciones);

  //Iteramos por estados hasta que los agotemos
  for(i=0;i<ListaEstadosNumEstados(listaEstados);i++){
    estadoActual = ListaEstadosNumEstado(listaEstados, i);
    transicionActual = (int*) calloc(numSimbolos,sizeof(int));

    //Iteramos para conseguir cada estado destino del símbolo para nuestro estado
    for(j=0;j<numSimbolos;j++){
      estadoSiguiente = AFNDClausuraLambda(afnd, AFNDEstadosDestino(afnd, estadoActual, j, AFNDNumEstados(afnd)));

      //Si el estado siguiente se encuentra en nuestra lista de estados, podemos
      //modificar ya la tabla de transiciones
      index = ListaEstadosExisteEstado(listaEstados, estadoSiguiente);
      if(index >= 0){
        transicionActual[j] = index;
      }
      //En caso contrario, hay que añadir una nueva entrada a la lista de estados
      //y a la de transiciones
      else{
        listaEstados = ListaEstadosInsertarEstado(listaEstados, estadoSiguiente);
        transiciones = TransicionesNuevaTransicion(transiciones);
        transicionActual[j] = ListaEstadosNumEstados(listaEstados) - 1;
      }
    }

    //Insertamos las transiciones de este estado en la tabla de transiciones
    transiciones = TransicionesInsertarTransicion(transiciones, transicionActual, i);
  }

  //Hemos conseguido nuestras tablas de estados y transiciones, queda generar el AFD
  afd = AFNDGenerarAFD(afnd, transiciones, listaEstados);

  BorrarEstado(listaEstados);
  BorrarTransiciones(transiciones);
  return afd;
}

//-------------------------FUNCIONES PRIVADAS--------------------------//
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

/*
Transforma una tabla binaria que representa a un estado
en una string única para ella
*/
char* _AFNDBinAString(AFND* afnd, int* tablaBin, int numEstados){
  char aux[STRLEN] = "";
  char* nombre;
  int i;

  for(i=0;i<numEstados;i++){
    if(tablaBin[i] == 1){
      strcat(aux, AFNDNombreEstadoEn(afnd, i));
    }
  }

  nombre = (char*)malloc(strlen(aux));
  strcpy(nombre,aux);

  return nombre;
}

/*
Calcula el tipo de estado de un cierto estado del AFD
*/
int _AFNDTipoEstado(AFND* afnd, ListaEstados* listaE, int numEstado){
  int* estado;
  int tipo = NORMAL, tipoAFND;
  int i;

  estado = ListaEstadosNumEstado(listaE, numEstado);

  if(numEstado == 0){
    tipo = INICIAL;
  }

  for(i=0;i<ListaEstadosNumEstados(listaE);i++){
    //Analizamos el estado del AFND si es que importa
    if(estado[i] == 1){
      tipoAFND = AFNDTipoEstadoEn(afnd, i);
      if(tipoAFND == FINAL || tipoAFND == INICIAL_Y_FINAL){
        if(tipo == NORMAL){
          tipo = FINAL;
        }
        else if(tipo == INICIAL){
          tipo = INICIAL_Y_FINAL;
        }
        break;
      }
    }
  }

  return tipo;
}

/*
Junta los unos de dos tablas binarias
*/
int* _AFNDMergeEstados(int* tablaBin, int* tablaBinAux, int tam){
  int i;

  for(i=0;i<tam;i++){
    tablaBin[i] = tablaBin[i] || tablaBinAux[i];
  }

  return tablaBin;
}
