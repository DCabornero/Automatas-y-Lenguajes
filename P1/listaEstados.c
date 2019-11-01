#include "listaEstados.h"

#define STRLEN 256

//////////////////////////////////////////////////////////////////////////////////
int* _AFNDClausuraBin(AFND* afnd, int estado, int numEstados);
int _ListaEstadosEstadoIgual(int** tablaProvisional, int* tablaBin, int lenProv, int lenBin);
//////////////////////////////////////////////////////////////////////////////////


struct _ListaEstados{
  int numEstados;
  int lenAFND;
  int** tabla;
  AFND* afnd;
};


ListaEstados* ListaEstadosNuevo(AFND* afnd){
  ListaEstados* listaEstados = NULL;
  int i = 0;
  int numEstados = 0, lenAFND = 0;
  int* tablaBin = NULL;
  int** tablaProvisional = NULL;

  listaEstados = (ListaEstados *) malloc(sizeof(ListaEstados));
  lenAFND = AFNDNumEstados(afnd);
  listaEstados->lenAFND = lenAFND;
  listaEstados->afnd = afnd;

  //Instanciamos una tabla provisional con la máxima longitud que vaya a tener
  tablaProvisional = calloc(lenAFND,sizeof(int*));

  for(i=0; i<lenAFND; i++){
    tablaBin = _AFNDClausuraBin(afnd, i ,lenAFND);

    if(_ListaEstadosEstadoIgual(tablaProvisional, tablaBin, i, lenAFND)==1){
      continue;
    }
    tablaProvisional[numEstados] = tablaBin;
    numEstados++;
  }

  listaEstados->numEstados = numEstados;
  //Instanciamos la tabla óptima
  listaEstados->tabla = calloc(numEstados,sizeof(int*));
  for(i=0;i<numEstados;i++){
    listaEstados->tabla[i] = tablaProvisional[i];
  }

  free(tablaProvisional);
  return listaEstados;
}


int ListaEstadosRelacionado(ListaEstados* lista, int estadoD, int estadoND){
  if(lista == NULL){
    printf("ERROR: LA LISTA NO EXISTE\n");
    exit(0);
  }

  if(estadoND >= (lista->lenAFND)){
    printf("ERROR: NO HAY TANTOS ESTADOS ASOCIADOS AL AFND\n");
    exit(0);
  }

  if(estadoD >= (lista->numEstados)){
    printf("ERROR: NO HAY TANTOS ESTADOS ASOCIADOS AL AFD\n");
    exit(0);
  }

  return lista->tabla[estadoD][estadoND];
}


char* ListaEstadosNombreEstado(ListaEstados* lista, int estado){
  int i = 0;
  char *nombreEstado, cadena[STRLEN] = "";
  int* tablaBin = NULL;

  if(lista == NULL){
    printf("ERROR: LA LISTA NO EXISTE\n");
    exit(0);
  }

  if(estado >= (lista->numEstados)){
    printf("ERROR: NO EXISTEN TANTOS ESTADOS EN LA LISTA\n");
    exit(0);
  }

  tablaBin = lista->tabla[estado];

  for(i=0;i<lista->lenAFND;i++){
    if(tablaBin[i]){
      strcat(cadena, AFNDNombreEstadoEn(lista->afnd, i));
      strcat(cadena, ",");
    }
  }
  cadena[strlen(cadena)-1] = 0;

  nombreEstado = (char*)malloc(strlen(cadena)*sizeof(char));
  strcpy(nombreEstado, cadena);

  return nombreEstado;
}


int ListaEstadosNumEstados(ListaEstados* lista){
  if(lista == NULL){
    printf("ERROR: LA LISTA NO EXISTE\n");
    exit(0);
  }

  return lista->numEstados;
}


//-------------------------FUNCIONES PRIVADAS--------------------------
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
Muestra si la tabla provisional tiene ya guardada la tabla binaria pasada o no
*/
int _ListaEstadosEstadoIgual(int** tablaProvisional, int* tablaBin, int lenProv, int lenBin){
  int i,j,flag;

  for(i=0; i<lenProv; i++){
    flag = 0;
    for(j=0; j<lenBin; j++){
      if(tablaProvisional[i][j] != tablaBin[j]){
        flag = 1;
        continue;
      }
    }
    if(flag == 0){
      return 1;
    }
  }
  return 0;
}
