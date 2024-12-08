all: LLRB.o AVL.o Conjunto.o  main.o
	gcc LLRB.o AVL.o Conjunto.o main.o -o main -std=c99 -Wall

LLRB.o:
	gcc -c LLRB.c -o LLRB.o

AVL.o:
	gcc -c AVL.c -o AVL.o

Conjunto.o:
	gcc -c Conjunto.c -o Conjunto.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	-rm *.o main

run:
	./main
