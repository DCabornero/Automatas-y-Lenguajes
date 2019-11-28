#include "minimiza.h"

AFND* AFNDMinimiza(AFND* afnd){

}

SetEstados* Reachable(AFND* afnd){
  int dest;
  SetEstados* reach = NULL;
  SetEstados* aux = NULL;
  SetEstados* descubiertos = NULL;
  int* listaBinReachable = NULL;
  int* listaBinAux = NULL;
  int* listaBinDescubiertos = NULL;
  int lenAFD = AFNDNumEstados(afnd);

  listaBinReachable = (int*) calloc(lenAFD, sizeof(int));
  listaBinReachable[AFNDIndiceEstadoInicial(afnd)] = 1;
  reach = crearSetEstados(lenAFD, listaBinReachable);

  listaBinAux = (int*) calloc(lenAFD, sizeof(int));
  aux = crearSetEstados(lenAFD, listaBinAux);

  listaBinDescubiertos = (int*) calloc(lenAFD, sizeof(int));
  listaBinDescubiertos[AFNDIndiceEstadoInicial(afnd)] = 1;
  descubiertos = crearSetEstados(lenAFD, listaBinDescubiertos);

  while(cardinalSetEstados(descubiertos) > 0){
    vaciarSetEstados(aux);
    for(i=0;i<lenAFD;i++){
      if(checkSetEstados[i]){
        for(j=0;j<AFNDNumSimbolos(afnd);j++){
          if(dest = AFNDTransicion(afnd, i, j) > -1){
            insertSetEstados(aux, dest);
          }
        }
      }
    }
  }
}

int AFNDTransicion(AFND* afnd, int inicial, int simbolo){
  int i = 0;
  for(i=0;i<AFNDNumEstados(afnd);i++){
    if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, inicial, simbolo, i)){
      return i;
    }
  }
  return -1;
}
