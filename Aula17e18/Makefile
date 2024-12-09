all: item.o AVL.o  main.o
	gcc item.o AVL.o main.o -o main -std=c99 -Wall

item.o:
	gcc -c item.c -o item.o

AVL.o:
	gcc -c AVL.c -o AVL.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	-rm *.o main

run:
	./main