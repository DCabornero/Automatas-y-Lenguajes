CC=gcc
CFLAGS= -Wall -g
CFLAGSAFND = -Wall -g
EJS = main

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)

listaEstados.o: listaEstados.c listaEstados.h
	$(CC) $(CFLAGSAFND) -c listaEstados.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGSAFND) -c afnd.c

main: main.o afnd.o listaEstados.o
	$(CC) $(CFLAGS) -o main main.o afnd.o listaEstados.o

main.o: main.c afnd.h listaEstados.h
	$(CC) $(CFLAGS) -c main.c

.PHONY: clean #Elimina los ejecutables y los .o
clean:
	rm -rf main.o listaEstados.o $(EJS)
