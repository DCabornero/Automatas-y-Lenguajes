#include "minimiza.h"

AFND* AFNDMinimiza(AFND* afnd){

}

SetEstados* Reachable(AFND* afnd){
  int dest;
  SetEstados* reach = NULL;
  SetEstados* aux = NULL;
  SetEstados* descubiertos = NULL;
  int lenAFD = AFNDNumEstados(afnd);

  /* Lista de estados alcanzables, empieza solo con el inicial*/
  /* Es equivalente a los nodos explorados*/
  reach = crearSetEstados(lenAFD);
  insertSetEstados(reach, AFNDIndiceEstadoInicial(afnd));

  /* Lista de estados auxiliar necesaria para el algoritmo, guarda los
  estados descubiertos en cada iteración (puede haber explorados entre ellso)*/
  aux = crearSetEstados(lenAFD);

  /* Lista de estados descubiertos en el algoritmo, empieza con el inicial*/
  descubiertos = crearSetEstados(lenAFD);
  insertSetEstados(descubiertos, AFNDIndiceEstadoInicial(afnd));

  /* El algoritmo es similar a la búsqueda en profundidad, por lo que parará
  cuando no queden estados descubiertos no explorados */
  while(cardinalSetEstados(descubiertos) > 0){
    vaciarSetEstados(aux);
    /* Desde los nodos descubiertos, guardamos en aux todos los estados a
    los que podamos llegar */
    for(i=0;i<lenAFD;i++){
      if(isInSetEstados(descubiertos, i)){
        for(j=0;j<AFNDNumSimbolos(afnd);j++){
          /* Si existe una transición a la que se llega desde el nodo
          descubierto con un cierto símbolo, lo guardamos en nuestro
          conjunto de estados auxiliar */
          if(dest = AFNDTransicion(afnd, i, j) != -1){
            insertSetEstados(aux, dest);
          }
        }
      }
    }
    /* Los estados descubiertos serán la lista obtenida menos los
    ya explorados */
    descubiertos = restaSetEstados(aux, reach);
    /* Damos por explorados todos los estados que pertenecían a la lista de
    descubiertos de esta iteración */
    reach = unionSetEstados(reach, descubiertos);
  }
  free(aux);
  free(descubiertos);
  return reach;
}


AFND* AFNDQuitarEstados(AFND* afnd, SetEstados* set){
  AFND* afd;
  
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
