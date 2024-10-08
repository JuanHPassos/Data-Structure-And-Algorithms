all: BFS.o item.o Fila.o
	gcc item.o Fila.o BFS.o -std=c99 -o BFS -Wall

BFS.o:
	gcc -c BFS.c -o BFS.o

Fila.o:
	gcc -c Fila.c -o Fila.o

item.o:
	gcc -c item.c -o item.o
clean:
	rm *.o BFS
run:
	./BFS < caso.in