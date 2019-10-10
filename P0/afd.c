#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 255
#define ASCIITOINDEX 65

//ESTRUCTURA DEL AFD.TXT
//Nº ESTADOS
//Nº LETRAS
//Nº ESTADOS FINALES
//Lista de estados finales
//for cada estado:
//  Nº TRANSICIONES
//  for cada trans:
//    LETRA
//    ESTADO


int main(int argc, char *argv[]){
  FILE* fp = NULL;
  char buf[MAXLEN];         //Buffer auxiliar
  int* finals = NULL;       //Array dinámico de estados finales
  int** transitions = NULL;   //Tabla
  int n = 0;    //Nº estados del autómata
  int i = 0, j = 0;
  int estado = 0;
  int letra = 0;
  int n_finals = 0; //Número de finales admitidos por el autómata
  int n_letras = 0; //Número de letras de la tabla (cols)
  int n_trans = 0; //Número de transiciones del estado actual

  //Comprobaciones
  if(argc != 3){
    printf("Error: Dos argumentos: nombre del fichero del autómata y palabra\n");
    return -1;
  }
  fp = fopen(argv[1], "r");
  if(!fp){
    printf("Error: Nombre de fichero incorrecto\n");
    return -1;
  }

	//Obtenemos lo datos iniciales de la tabla
  fgets(buf, MAXLEN, fp);
  n = atoi(buf);
  fgets(buf, MAXLEN, fp);
  n_letras = atoi(buf);
  fgets(buf, MAXLEN, fp);
  n_finals = atoi(buf);

  finals = (int*)calloc(n_finals, sizeof(int));
  for(i=0;i<n_finals;i++){
    fgets(buf, MAXLEN, fp);
    finals[i] = atoi(buf);
  }

	//Reservamos la memoria para la tabla e incicializamos todas las casillas a -1
  transitions = (int**)calloc(n, sizeof(int*));
  for(i=0;i<n;i++){
    transitions[i] = (int*)calloc(n_letras, sizeof(int));
    for(j=0;j<n_letras;j++){
      transitions[i][j] = -1;
    }
  }

	//Rellenamos nuestra tabla con los datos de nuestro autómata
  for(i=0;i<n;i++){
    fgets(buf, MAXLEN, fp);
    n_trans = atoi(buf);
    for(j=0;j<n_trans;j++){
      fgets(buf, MAXLEN, fp);
      letra = (int)buf[0]-ASCIITOINDEX;
      fgets(buf, MAXLEN, fp);
      transitions[i][letra] = atoi(buf);
    }
  }

  //Recorremos la palabra
  for(i=0;argv[2][i] != 0;i++){
    letra = (int)argv[2][i]-ASCIITOINDEX;
    if(transitions[estado][letra] == -1){
      printf("La palabra no ha sido reconocida.\n");
      return 0;
    }
    estado = transitions[estado][letra];
  }

  //Identificamos si nos encontramos en un estado final
  for(i=0;i<n_finals;i++){
    if(estado == finals[i]){
      printf("La palabra si ha sido reconocida.\n");
      return 0;
    }
  }
  printf("La palabra no ha sido reconocida.\n");
  return 0;
}
