#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;

	p_afnd= AFNDNuevo("afnd3", 6, 4);

	AFNDInsertaSimbolo(p_afnd,"+");
	AFNDInsertaSimbolo(p_afnd, "-");
  AFNDInsertaSimbolo(p_afnd, ".");
  /*Dígito en genérico*/
	AFNDInsertaSimbolo(p_afnd,"d");

	AFNDInsertaEstado(p_afnd, "q0", INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", NORMAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", FINAL);

	AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "-", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "d", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "d", "q4");
	AFNDInsertaTransicion(p_afnd, "q1", ".", "q2");
	AFNDInsertaTransicion(p_afnd, "q2", "d", "q3");
	AFNDInsertaTransicion(p_afnd, "q3", "d", "q3");
	AFNDInsertaTransicion(p_afnd, "q4", ".", "q3");

	AFNDInsertaLTransicion(p_afnd, "q0", "q1");
	AFNDInsertaLTransicion(p_afnd, "q3", "q5");
	AFNDCierraLTransicion(p_afnd);

	afd = AFNDTransforma(p_afnd);
	/*AFNDImprime(stdout,afd);*/
	AFNDADot(afd);

	AFNDElimina(afd);
	AFNDElimina(p_afnd);

	return 0;
}
