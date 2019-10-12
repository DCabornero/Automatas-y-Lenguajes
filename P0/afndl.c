#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 255
#define ASCIITOINDEX 97

//ESTRUCTURA DEL AFNDL.TXT
//Nº ESTADOS
//Nº LETRAS
//Nº ESTADOS FINALES
//Lista de estados finales
//for cada estado:
//  Nº TRANSICIONES
//  for cada trans:
//    LETRA
//    for cada letra:
//    Nº ESTADOS
//    ESTADOS
//Nª ESTADOS CON TRANS LAMBDA
//for cada uno de estos estados:
//  ESTADO
//  Nª ESTADOS A LOS QUE SE LLEGA
//  LISTA DE ESTADOS

int cierre_lambda(int* estados, int* trans_letra, int* trans_lambda, int*** transitions, int** transitions_l, int letra);
int cierre_lambda_sinletra(int* estados, int* trans_lambda, int** transitions_l);

int main(int argc, char *argv[]){
  FILE* fp = NULL;
  char buf[MAXLEN];         //Buffer auxiliar
  int* finals = NULL;       //Array dinámico de estados finales
  int*** transitions = NULL;   //Tabla
  int** transitions_l = NULL; //Tabla de transiciones lambda
  int n = 0;    //Nº estados del autómata
  int i = 0, j = 0, k = 0;
  int flag_fin = 0;
  int n_lambdas = 0;
  int state = 0;
  int* estados_ant = NULL, *estados_post = NULL, *aux = NULL;
  int letra = 0;
  int n_finals = 0; //Número de finales admitidos por el autómata
  int n_letras = 0; //Número de letras de la tabla (cols)
  int n_trans = 0; //Número de transiciones del estado actual
  int n_estados_trans = 0;

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

  //Reservamos la memoria para el array de estados
  estados_ant = (int*)calloc(n, sizeof(int));
  estados_post = (int*)calloc(n, sizeof(int));
  //Establecemos el estado inicial
  estados_ant[0] = 1;

	//Reservamos la memoria para la tabla e incicializamos todas las casillas a NULL
  transitions = (int***)calloc(n, sizeof(int**));
  for(i=0;i<n;i++){
    transitions[i] = (int**)calloc(n_letras, sizeof(int*));
    for(j=0;j<n_letras;j++){
      transitions[i][j] = NULL;
    }
  }

  transitions_l = (int**)calloc(n, sizeof(int*));
  for(i=0;i<n;i++){
    transitions_l[i]=NULL;
  }

	//Rellenamos nuestra tabla con los datos de nuestro autómata
  for(i=0;i<n;i++){
    fgets(buf, MAXLEN, fp);
    n_trans = atoi(buf);
    for(j=0;j<n_trans;j++){
      fgets(buf, MAXLEN, fp);
      letra = (int)buf[0]-ASCIITOINDEX;
      fgets(buf, MAXLEN, fp);
      n_estados_trans = atoi(buf);
      transitions[i][letra] = (int*)calloc(n_estados_trans+1, sizeof(int));
      transitions[i][letra][0] = n_estados_trans;
      for(k=1; k<n_estados_trans+1; k++){
        fgets(buf, MAXLEN, fp);
        transitions[i][letra][k] = atoi(buf);
      }
    }
  }

  //Rellenamos la tabla de transiciones transiciones lambda
  fgets(buf, MAXLEN, fp);
  n_lambdas = atoi(buf);
  for(i=0;i<n_lambdas;i++){
    fgets(buf, MAXLEN, fp);
    state = atoi(buf);
    fgets(buf, MAXLEN, fp);
    n_trans = atoi(buf);
    transitions_l[state] = calloc(n_trans+1, sizeof(int));
    transitions_l[state][0] = n_trans;
    for(j=1;j<n_trans+1;j++){
      fgets(buf, MAXLEN, fp);
      transitions_l[state][j] = atoi(buf);
    }
  }
  //Recorremos la palabra
  for(i=0;argv[2][i] != 0;i++){
    letra = (int)argv[2][i]-ASCIITOINDEX;
    for(j=0;j<n;j++){
      if(estados_ant[j]){
        if(transitions[j][letra] != NULL){
          cierre_lambda(estados_post, transitions[j][letra], transitions_l[j], transitions, transitions_l, letra);
        }
      }
    }
    aux = estados_ant;
    estados_ant = estados_post;
    estados_post = aux;
    for(j=0;j<n;j++){
      estados_post[j] = 0;
    }
    flag_fin = 1;
    for(j=0;j<n;j++){
      if(estados_ant[j]){
        flag_fin = 0;
        break;
      }
    }
    if(flag_fin){
      printf("La palabra no ha sido reconocida.\n");
      return 0;
    }
  }

  //Identificamos si nos encontramos en un estado final
  for(i=0;i<n_finals;i++){
    if(estados_ant[finals[i]]){
      printf("La palabra si ha sido reconocida.\n");
      return 0;
    }
  }
  printf("La palabra no ha sido reconocida.\n");
  return 0;
}

int cierre_lambda(int* estados, int* trans_letra, int* trans_lambda, int*** transitions, int** transitions_l, int letra){
  int i = 0;
  if(trans_letra != NULL){
    for(i=1 ;i<trans_letra[0]+1; i++){
      estados[trans_letra[i]] = 1;
      cierre_lambda_sinletra(estados, transitions_l[trans_letra[i]], transitions_l);
    }
  }
  if(trans_lambda != NULL){
    for(i=1 ;i<trans_lambda[0]+1; i++){
      estados[trans_lambda[i]] = 1;
      cierre_lambda(estados, transitions[trans_lambda[i]][letra], transitions_l[trans_lambda[i]], transitions, transitions_l, letra);
    }
  }
  return 0;
}

int cierre_lambda_sinletra(int* estados, int* trans_lambda, int** transitions_l){
  int i = 0;
  if(trans_lambda != NULL){
    for(i=1 ;i<trans_lambda[0]+1; i++){
      estados[trans_lambda[i]] = 1;
      cierre_lambda_sinletra(estados, transitions_l[trans_lambda[i]], transitions_l);
    }
  }
  return 0;
}
