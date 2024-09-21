all: main.o item.o MyDeque.o
	gcc item.o MyDeque.o main.o -std=c99 -o main -Wall

main.o:
	gcc -c main.c -o main.o

MyDeque.o:
	gcc -c MyDeque.c -o MyDeque.o

item.o:
	gcc -c item.c -o item.o
clean:
	rm *.o main
run:
	./main