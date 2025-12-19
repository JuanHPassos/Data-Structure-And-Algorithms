all: item.o arvorebinaria.o main.o
	gcc item.o arvorebinaria.o main.o -o arvorebinaria -std=c99 -Wall
	
item.o:
	gcc -c item.c -o item.o

arvorebinaria.o:
	gcc -c arvorebinaria.c -o arvorebinaria.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o arvorebinaria

run:
	./arvorebinaria