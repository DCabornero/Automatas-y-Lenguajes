CC=gcc
CFLAGS= -Wall -g
CFLAGSAFND = -Wall -g
EJS = main

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)

transiciones.o: transiciones.c transiciones.h
	$(CC) $(CFLAGSAFND) -c transiciones.c

listaEstados.o: listaEstados.c listaEstados.h
	$(CC) $(CFLAGSAFND) -c listaEstados.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGSAFND) -c afnd.c

main: main.o afnd.o listaEstados.o transiciones.o
	$(CC) $(CFLAGS) -o main main.o afnd.o listaEstados.o transiciones.o

main.o: main.c afnd.h listaEstados.h transiciones.h
	$(CC) $(CFLAGS) -c main.c

.PHONY: clean #Elimina los ejecutables y los .o
clean:
	rm -rf main.o listaEstados.o transiciones.o $(EJS)
