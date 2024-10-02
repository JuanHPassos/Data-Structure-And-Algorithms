all: Grafo.c Lista.o main.o
	gcc Grafo.c Lista.o main.o -o main -std=c99 -Wall

Grafo.o:
	gcc -c Grafo.c -o Grafo.o

Lista.o:
	gcc -c Lista.c -o Lista.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	-rm *.o main

run:
	./main < caso.in