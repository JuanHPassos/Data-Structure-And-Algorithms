all: item.o Lista.o main.o
	gcc item.o Lista.o main.o -o Lista -std=c99 -Wall
	
item.o:
	gcc -c item.c -o item.o

Lista.o:
	gcc -c Lista.c -o Lista.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o Lista

run:
	./Lista