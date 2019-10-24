CC=gcc
CFLAGS= -Wall -g -pedantic
CFLAGSAFND = -Wall -g
EJS = main

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGSAFND) -c afnd.c

main: main.o afnd.o
	$(CC) $(CFLAGS) -o main main.o afnd.o

main.o: main.c afnd.h
	$(CC) $(CFLAGS) -c main.c

.PHONY: clean #Elimina los ejecutables, los .asm y los .o
clean:
	rm -rf main.o $(EJS)
