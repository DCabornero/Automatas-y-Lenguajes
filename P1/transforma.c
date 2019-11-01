#include "transforma.h"

char* AFNDClausuraLambda(AFND* afnd, int estado){
  int numEstados;
  int* tablaBin = NULL;
  char* nombre = NULL

  numEstados = AFNDNumEstados(afnd);
  tablaBin = _AFNDClausuraBin(afnd, estado, numEstados);
  nombre = _AFNDBinAString(afnd, tablaBin, numEstados);

  return nombre;
}
