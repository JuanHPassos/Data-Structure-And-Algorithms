all: item.o LLRB.o  main.o
	gcc item.o LLRB.o main.o -o main -std=c99 -Wall

item.o:
	gcc -c item.c -o item.o

LLRB.o:
	gcc -c LLRB.c -o LLRB.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	-rm *.o main

run:
	./main