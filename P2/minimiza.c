#include "minimiza.h"

/**********************************************************************/
SetEstados* _AFNDEstadosTransitables(AFND* afd, SetEstados* ini);
/**********************************************************************/

/*AFND* AFNDMinimiza(AFND* afnd){

}*/

SetEstados* Reachable(AFND* afnd){
  SetEstados* reach = NULL;
  SetEstados* aux = NULL;
  SetEstados* descubiertos = NULL;
  int i, j;
  int dest;
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
    zerosSetEstados(aux);
    /* Desde los nodos descubiertos, guardamos en aux todos los estados a
    los que podamos llegar */
    for(i=0;i<lenAFD;i++){
      if(isInSetEstados(descubiertos, i)){
        for(j=0;j<AFNDNumSimbolos(afnd);j++){
          /* Si existe una transición a la que se llega desde el nodo
          descubierto con un cierto símbolo, lo guardamos en nuestro
          conjunto de estados auxiliar */
          dest = AFNDTransicion(afnd, i, j);
          if(dest != -1){
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
  liberarSetEstados(aux);
  liberarSetEstados(descubiertos);
  return reach;
}


AFND* AFNDQuitarEstados(AFND* afdinicial, SetEstados* set){
  AFND* afd;
  int i, j;
  int numSimbolos, numEstados;
  int destino;
  char** listaNombres;

  numEstados = cardinalSetEstados(set);
  numSimbolos = AFNDNumSimbolos(afdinicial);

  listaNombres = (char**) malloc(numEstados*sizeof(char*));

  afd = AFNDNuevo("afdreachable", numEstados, numSimbolos);

  /* Insertamos los símbolos, idénticos al autómata inicial */
  for(i=0;i<numSimbolos; i++){
    AFNDInsertaSimbolo(afd, AFNDSimboloEn(afdinicial, i));
  }

  /* Insertamos los estados que necesitamos al afd y
   obtenemos la lista de nombres de estados del afd (facilita cálculos)*/
  for(i=0;i<AFNDNumEstados(afdinicial);i++){
    if(isInSetEstados(set,i)){
      listaNombres[j] = AFNDNombreEstadoEn(afdinicial,i);
      AFNDInsertaEstado(afd, listaNombres[j], AFNDTipoEstadoEn(afdinicial, i));
      j++;
    }
  }

  /* Insertamos las transiciones correspondientes */
  for(i=0;i<numEstados;i++){
    for(j=0;j<numEstados;j++){
      /* Obtenemos el destino de la transicion en el afd inicial*/
      destino = AFNDTransicion(afdinicial, i, j);
      if(destino == -1) continue;
      /* Obtenemos (si existe) el destino de la transicion de nuestro afd*/
      destino = AFNDIndiceDeEstado(afd, AFNDNombreEstadoEn(afdinicial,destino));
      if(destino != -1){
        AFNDInsertaTransicion(afd, listaNombres[i], AFNDSimboloEn(afd,j), listaNombres[destino]);
      }
    }
  }

  AFNDCierraLTransicion(afd);
  free(listaNombres);

  return afd;
}


Particion* NonDistinguishable(AFND* afnd){
  Particion* descubiertos;
  Particion* finalPart;
  SetEstados *finales, *explorando, *transitables, *division;
  SetEstados *interseccion, *resta;
  int i, j;
  int numEstados, numSimbolos, tamFinalPart;
  int tipoEstado, posicion;

  /* En la primera partición guardamos los conjuntos que iremos explorando*/
  /* En la segunda aquellos conjuntos distinguibles*/
  descubiertos = ParticionInstancia(afnd);
  finalPart = ParticionInstancia(afnd);

  numEstados = AFNDNumEstados(afnd);
  numSimbolos = AFNDNumSimbolos(afnd);

  /* Calculamos dos estados finales, para introducirlos en nuestras dos particiones*/
  finales = crearSetEstados(numEstados);

  for(i=0;i<numEstados;i++){
    tipoEstado = AFNDTipoEstadoEn(afnd, i);
    if(tipoEstado == FINAL || tipoEstado == INICIAL_Y_FINAL){
      insertSetEstados(finales, i);
    }
  }

  ParticionInsertarSetEstados(descubiertos, copiarSetEstados(finales));
  ParticionInsertarSetEstados(finalPart, copiarSetEstados(finales));

  /*Introducimos además su complementario*/
  ParticionInsertarSetEstados(descubiertos, complementarioSetEstados(finales));
  ParticionInsertarSetEstados(finalPart, complementarioSetEstados(finales));

  liberarSetEstados(finales);
  /*Iteramos hasta que no queden conjuntos que descubrir*/
  while(ParticionNumSetEstados(descubiertos) > 0){
    /* Exploramos el primer conjunto de la lista de descubiertos*/
    explorando = ParticionPopSetEstados(descubiertos,0);

    /* Iteramos sobre todos los símbolos*/
    for(i=0;i<numSimbolos;i++){
      /*Hallamos los estados hasta los que podemos llegar desde el conjunto
      actual mediante una sola transicion*/
      transitables = _AFNDEstadosTransitables(afnd, explorando);

      tamFinalPart = ParticionNumSetEstados(finalPart);
      /*Extraemos los conjuntos de finalPart, y no los metemos si su intersección
      y su resta con 'transitables' es no vacía*/
      for(j=0;j<tamFinalPart;j++){
        division = ParticionPopSetEstados(finalPart, 0);
        interseccion = interseccionSetEstados(division, transitables);
        resta = restaSetEstados(division, transitables);
        /*Si alguno de los dos conjuntos es vacío, no hay nada que hacer.
        Introducimos de nuevo el conjunto*/
        if(cardinalSetEstados(interseccion) || cardinalSetEstados(resta)){
          ParticionInsertarSetEstados(finalPart, copiarSetEstados(division));
        }
        /* Si ambas operaciones son no vacías, trabajamos con ellas*/
        else{
          /*En primer lugar, reemplazamos el conjunto anterior por estos dos nuevos*/
          ParticionInsertarSetEstados(finalPart, copiarSetEstados(interseccion));
          ParticionInsertarSetEstados(finalPart, copiarSetEstados(resta));
          /*Toca actualizar la particion de conjuntos descubiertos*/
          posicion = isInParticionSetEstados(descubiertos, division);
          /* Si el conjunto estaba en estados descubiertos, lo sacamos e introducimos
          los dos nuevos conjuntos*/
          if(posicion != -1){
            /*Como el pop me devuelve division, la libero y la obtengo de nuevo*/
            liberarSetEstados(division);
            division = ParticionPopSetEstados(descubiertos, posicion);
            ParticionInsertarSetEstados(descubiertos, copiarSetEstados(interseccion));
            ParticionInsertarSetEstados(descubiertos, copiarSetEstados(resta));
          }
          /*Si no estaba, insertamos la interseccion o la resta (en concreto el que
          menos estados tenga), ya que introducir los dos sería redundante*/
          else{
            if(cardinalSetEstados(interseccion) <= cardinalSetEstados(resta)){
              ParticionInsertarSetEstados(descubiertos, copiarSetEstados(interseccion));
            }
            else{
              ParticionInsertarSetEstados(descubiertos, copiarSetEstados(resta));
            }
          }
        }
        liberarSetEstados(division);
        liberarSetEstados(interseccion);
        liberarSetEstados(resta);
      }
      liberarSetEstados(transitables);
    }
    liberarSetEstados(explorando);
  }
  BorrarParticion(descubiertos);

  return finalPart;
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

/***********************FUNCIONES PRIVADAS**************************/
/* Devulve el conjunto de estados a los que se puede llegar a través de
una transición desde los estados del conjunto*/
SetEstados* _AFNDEstadosTransitables(AFND* afd, SetEstados* ini){
  int numSimbolos, numEstados, destino;
  int i,j;
  SetEstados* transitables;

  numSimbolos = AFNDNumSimbolos(afd);
  numEstados = AFNDNumEstados(afd);

  transitables = crearSetEstados(numEstados);

  for(i=0;i<numEstados;i++){
    if(isInSetEstados(ini, i)){
      for(j=0;j<numSimbolos;j++){
        destino = AFNDTransicion(afd, i, j);
        if(destino != -1){
          insertSetEstados(transitables, destino);
        }
      }
    }
  }

  return transitables;
}
