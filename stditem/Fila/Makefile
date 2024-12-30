all: main.o item.o Fila.o
	gcc item.o Fila.o main.o -std=c99 -o main -Wall

main.o:
	gcc -c main.c -o main.o

Fila.o:
	gcc -c Fila.c -o Fila.o

item.o:
	gcc -c item.c -o item.o
clean:
	-rm *.o main
run:
	./main