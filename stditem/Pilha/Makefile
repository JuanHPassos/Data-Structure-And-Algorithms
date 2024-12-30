all: main.o item.o Pilha.o
	gcc item.o Pilha.o main.o -std=c99 -o main -Wall

main.o:
	gcc -c main.c -o main.o

Pilha.o:
	gcc -c Pilha.c -o Pilha.o

item.o:
	gcc -c item.c -o item.o
clean:
	-rm *.o main
run:
	./main