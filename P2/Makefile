CC=gcc
CFLAGS= -Wall -ansi -pedantic -g --debug
CFLAGSAFND = -Wall -ansi -g --debug
EJS = ejemplo1 ejemplo2
EJSO = ejemplo1.o ejemplo2.o
TADSO = setEstados.o particion.o minimiza.o
TADSH = afnd.h setEstados.h particion.h minimiza.h

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)
	@echo "Instrucciones del Makefile:"
	@echo "	make clean: Para borrar todos los .o menos afnd.o"
	@echo "	make cleanall: Para borrar todos los .o"
	@echo "	make png: ejecuta el programa que se le proporcione como input y da tanto el .dot como el .png del afd"

minimiza.o: minimiza.c minimiza.h
	$(CC) $(CFLAGS) -c minimiza.c

particion.o: particion.c particion.h
	$(CC) $(CFLAGS) -c particion.c

setEstados.o: setEstados.c setEstados.h
	$(CC) $(CFLAGS) -c setEstados.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGSAFND) -c afnd.c

ejemplo1: ejemplo1.o afnd.o $(TADSO)
	$(CC) $(CFLAGS) -o ejemplo1 ejemplo1.o afnd.o $(TADSO)

ejemplo1.o: ejemplo1.c $(TADSH)
	$(CC) $(CFLAGS) -c ejemplo1.c

ejemplo2: ejemplo2.o afnd.o $(TADSO)
	$(CC) $(CFLAGS) -o ejemplo2 ejemplo2.o afnd.o $(TADSO)

ejemplo2.o: ejemplo2.c $(TADSH)
	$(CC) $(CFLAGS) -c ejemplo2.c

.PHONY: clean #Elimina los ejecutables y los .o excepto afnd.o
clean:
	rm -rf $(TADSO) $(EJS) $(EJSO)

.PHONY: cleanall #Elimina los ejecutables y los .o
cleanall:
	rm -rf afnd.o $(TADSO) $(EJS) $(EJSO)

.PHONY: png
png:
	@read -p "Introduce el nombre del ejecutable: " executable; \
	./$$executable; \
	dot -Tpng afd.dot -o afd.png
