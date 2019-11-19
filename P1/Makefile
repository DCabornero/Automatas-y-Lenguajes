CC=gcc
CFLAGS= -Wall -ansi -pedantic -g --debug
CFLAGSAFND = -Wall -ansi -g --debug
EJS = ejemplo1 ejemplo2 ejemplo3
EJSO = listaEstados.o transiciones.o transforma.o

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)
	@echo "Instrucciones del Makefile:"
	@echo "	make clean: Para borrar todos los .o menos afnd.o"
	@echo "	make cleanall: Para borrar todos los .o"
	@echo "	make png: ejecuta el programa que se le proporcione como input y da tanto el .dot como el .png del afd"

transiciones.o: transiciones.c transiciones.h
	$(CC) $(CFLAGS) -c transiciones.c

listaEstados.o: listaEstados.c listaEstados.h
	$(CC) $(CFLAGS) -c listaEstados.c

transforma.o: transforma.c transforma.h
	$(CC) $(CFLAGS) -c transforma.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGSAFND) -c afnd.c

ejemplo1: ejemplo1.o afnd.o $(EJSO)
	$(CC) $(CFLAGS) -o ejemplo1 ejemplo1.o afnd.o $(EJSO)

ejemplo1.o: ejemplo1.c afnd.h listaEstados.h transiciones.h transforma.h
	$(CC) $(CFLAGS) -c ejemplo1.c

ejemplo2: ejemplo2.o afnd.o $(EJSO)
	$(CC) $(CFLAGS) -o ejemplo2 ejemplo2.o afnd.o $(EJSO)

ejemplo2.o: ejemplo2.c afnd.h listaEstados.h transiciones.h transforma.h
	$(CC) $(CFLAGS) -c ejemplo2.c

ejemplo3: ejemplo3.o afnd.o $(EJSO)
	$(CC) $(CFLAGS) -o ejemplo3 ejemplo3.o afnd.o $(EJSO)

ejemplo3.o: ejemplo3.c afnd.h listaEstados.h transiciones.h transforma.h
	$(CC) $(CFLAGS) -c ejemplo3.c

.PHONY: clean #Elimina los ejecutables y los .o excepto afnd.o
clean:
	rm -rf ejemplo1.o ejemplo2.o ejemplo3.o $(EJSO) $(EJS)

.PHONY: cleanall #Elimina los ejecutables y los .o
cleanall:
	rm -rf ejemplo1.o ejemplo2.o ejemplo3.o afnd.o $(EJSO) $(EJS)

.PHONY: png
png:
	@read -p "Introduce el nombre del ejecutable: " executable; \
	./$$executable; \
	dot -Tpng afd.dot -o afd.png
