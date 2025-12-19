all: main.o item.o Lista.o
	gcc item.o Lista.o main.o -std=c99 -o main -Wall

main.o:
	gcc -c main.c -o main.o

Lista.o:
	gcc -c Lista.c -o Lista.o

item.o:
	gcc -c item.c -o item.o
clean:
	rm *.o main
run:
	./main