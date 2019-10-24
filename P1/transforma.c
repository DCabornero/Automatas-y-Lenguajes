#include "transforma.h"

#define STRLEN 256
/*

*/
int* _AFNDClausuraBin(AFND* afnd, int estado, int numEstados);
char* _AFNDBinAString(AFND* afnd, int* tablaBin, int numEstados);

char* AFNDClausuraLambda(AFND* afnd, int estado){

}

AFND* AFNDTransforma(AFND* afnd){
  //TODO
}

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

char* _AFNDBinAString(AFND* afnd, int* tablaBin, int numEstados){
  int i = 0;
  char nombreEstado[STRLEN] = "";

  for(i=0;i<numEstados;i++){
    if(tablaBin[i]){
      strcat(nombreEstado, AFNDNombreEstadoEn(afnd, i));
      strcat(nombreEstado, ",");
    }
  }
  nombreEstado[strlen(nombreEstado)-1] = 0;
  return nombreEstado;
}
