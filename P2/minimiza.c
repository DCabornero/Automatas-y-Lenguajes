#include "minimiza.h"
#define STRLEN 256
#define TOASCII 48

/**********************************************************************/
char* _AFNDFabricaNombre(AFND* afnd, Particion* particion, int index);
SetEstados* _AFNDEstadosTransitables(AFND* afd, SetEstados* ini, int simbolo);
int _AFNDFabricaStatus(AFND* afnd, Particion* particion, int index);
int _AFNDParticionTransita(AFND* afnd, Particion* particion, int inicial, int simbolo);
/**********************************************************************/

AFND* AFNDMinimiza(AFND* afnd){
  SetEstados* reach;
  AFND *reachable, *final;
  Particion* particion;

  reach = Reachable(afnd);
  reachable = AFNDQuitarEstados(afnd, reach);
  particion = NonDistinguishable(reachable);
  final = AFNDFabricaParticion(reachable, particion);
  AFNDElimina(reachable);

  return final;
}

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
  int i, j = 0;
  int numSimbolos, numEstados;
  int origen, destino;
  char** listaNombres;

  numEstados = cardinalSetEstados(set);
  numSimbolos = AFNDNumSimbolos(afdinicial);

  listaNombres = (char**) malloc(numEstados*sizeof(char*));

  afd = AFNDNuevo("afd", numEstados, numSimbolos);

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
    for(j=0;j<numSimbolos;j++){
      /* Obtenemos el origen y el destino de la transicion en el afd inicial*/
      origen = AFNDIndiceDeEstado(afdinicial, AFNDNombreEstadoEn(afd, i));
      destino = AFNDTransicion(afdinicial, origen, j);
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
      /*Hallamos los estados desde los que podemos llegar al conjunto
      actual mediante una sola transicion*/
      transitables = _AFNDEstadosTransitables(afnd, explorando, i);

      tamFinalPart = ParticionNumSetEstados(finalPart);
      /*Extraemos los conjuntos de finalPart, y no los metemos si su intersección
      y su resta con 'transitables' es no vacía*/
      for(j=0;j<tamFinalPart;j++){
        division = ParticionPopSetEstados(finalPart, 0);
        interseccion = interseccionSetEstados(division, transitables);
        resta = restaSetEstados(division, transitables);
        /*Si alguno de los dos conjuntos es vacío, no hay nada que hacer.
        Introducimos de nuevo el conjunto*/
        if(!(cardinalSetEstados(interseccion) && cardinalSetEstados(resta))){
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

AFND* AFNDFabricaParticion(AFND* afdinicial, Particion* particion){
  AFND* afd;
  char* nombre;
  int numEstados, numSimbolos, status, transicion;
  int i, j;

  numSimbolos = AFNDNumSimbolos(afdinicial);
  numEstados = ParticionNumSetEstados(particion);

  /* Habrá el mismo número de símbolos y tantos estados como particiones */
  afd = AFNDNuevo("afd", numEstados, numSimbolos);

  /* Insertamos los símbolos */
  for(i=0;i<numSimbolos;i++){
    AFNDInsertaSimbolo(afd,AFNDSimboloEn(afdinicial, i));
  }

  /* Insertamos los estados */
  for(i=0;i<numEstados;i++){
    nombre = _AFNDFabricaNombre(afdinicial, particion, i);
    status = _AFNDFabricaStatus(afdinicial, particion, i);
    AFNDInsertaEstado(afd, nombre, status);
    free(nombre);
  }

  /*Insertamos las transiciones */
  for(i=0;i<numEstados;i++){
    for(j=0;j<numSimbolos;j++){
      transicion = _AFNDParticionTransita(afdinicial, particion, i, j);
      if(transicion != -1){
        AFNDInsertaTransicion(afd,
            AFNDNombreEstadoEn(afd, i),
            AFNDSimboloEn(afd, j),
            AFNDNombreEstadoEn(afd, transicion));
      }
    }
  }

  return afd;
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
SetEstados* _AFNDEstadosTransitables(AFND* afd, SetEstados* ini, int simbolo){
  int numEstados, destino;
  int i,j;
  SetEstados* transitables;

  numEstados = AFNDNumEstados(afd);

  transitables = crearSetEstados(numEstados);

  for(i=0;i<numEstados;i++){
    if(isInSetEstados(ini, i)){
      for(j=0;j<numEstados;j++){
        destino = AFNDTransicion(afd, j, simbolo);
        if(destino == i){
          insertSetEstados(transitables, j);
        }
      }
    }
  }

  return transitables;
}

/* Devuelve el nombre del conjunto de estados index-esimo de la particion */
char* _AFNDFabricaNombre(AFND* afnd, Particion* particion, int index){
  int* listaBin;
  char aux[STRLEN] = "q";
  char* nombre;
  int i;

  listaBin = ParticionNesimaListaBin(particion, index);

  for(i=0;i<AFNDNumEstados(afnd);i++){
    if(listaBin[i] == 1){
      strcat(aux, "_");
      strcat(aux, AFNDNombreEstadoEn(afnd, i)+1);
    }
  }

  nombre = (char*) malloc((strlen(aux)+1)*sizeof(char));
  strcpy(nombre, aux);
  return nombre;
}

/* Devuelve el status de un cierto conjunto de la partición */
int _AFNDFabricaStatus(AFND* afnd, Particion* particion, int index){
  int* listaBin;
  int i;

  listaBin = ParticionNesimaListaBin(particion, index);

  /* Si el estado inicial se encuentra en la partición, el tipo de estado del conjunto
  será el tipo de estado del estado inicial (ya que si también es final el estado
  inicial, el conjunto es estado final)*/
  if(listaBin[AFNDIndiceEstadoInicial(afnd)] == 1){
    return AFNDTipoEstadoEn(afnd, AFNDIndiceEstadoInicial(afnd));
  }
  /*Los estados finales están particionados, es decir, los conjuntos con estados
  finales solo tienen estados finales, y aquellos que tienen algún estado no final
  no tienen ningún estado final. Por tanto, cambiaremos el estado a final en la
  primera aparición.*/
  for(i=0;i<AFNDNumEstados(afnd);i++){
    if(listaBin[i] == 1){
      return AFNDTipoEstadoEn(afnd, AFNDTipoEstadoEn(afnd, i));
    }
  }
  /* Aquí no se debería llegar, pero bueno, los warnings */
  return NORMAL;
}


/* En caso que exista una transición que vaya a un conjunto de estados desde el
conjunto 'inicial' con un cierto símbolo, devuelve el índice del conjunto destino.
Si no existe, devuelve -1 */
int _AFNDParticionTransita(AFND* afnd, Particion* particion, int inicial, int simbolo){
  int transicion;
  int* listaBin, *listaBinDest;
  int i, j;

  listaBin = ParticionNesimaListaBin(particion, inicial);

  /* Solo necesitamos el primer estado que encontremos en el conjunto.
  Tendremos que ver a qué estado llega, y dónde se encuentra ese estado */
  for(i=0;i<AFNDNumEstados(afnd);i++){
    if(listaBin[i] == 1){
      transicion = AFNDTransicion(afnd, i, simbolo);

      if(transicion == -1){
        return -1;
      }

      for(j=0;j<ParticionNumSetEstados(particion);j++){
        listaBinDest = ParticionNesimaListaBin(particion, j);
        if(listaBinDest[transicion] == 1){
          return j;
        }
      }
    }
  }
  /* Aquí no se debería llegar, pero bueno, los warnings */
  return -2;
}
