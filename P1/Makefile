CC=gcc
CFLAGS= -Wall -g
CFLAGSAFND = -Wall -g
EJS = main
EJSO = listaEstados.o transiciones.o transforma.o

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)

transiciones.o: transiciones.c transiciones.h
	$(CC) $(CFLAGSAFND) -c transiciones.c

listaEstados.o: listaEstados.c listaEstados.h
	$(CC) $(CFLAGSAFND) -c listaEstados.c

transforma.o: transforma.c transforma.h
	$(CC) $(CFLAGSAFND) -c transforma.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGSAFND) -c afnd.c

main: main.o afnd.o $(EJSO)
	$(CC) $(CFLAGS) -o main main.o afnd.o $(EJSO)

main.o: main.c afnd.h listaEstados.h transiciones.h transforma.h
	$(CC) $(CFLAGS) -c main.c

.PHONY: clean #Elimina los ejecutables y los .o
clean:
	rm -rf main.o $(EJSO) $(EJS)
