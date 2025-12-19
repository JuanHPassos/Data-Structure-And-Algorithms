all: item.o ABB.o main.o
	gcc item.o ABB.o main.o -o ABB -std=c99 -Wall
	
item.o:
	gcc -c item.c -o item.o

ABB.o:
	gcc -c ABB.c -o ABB.o
	 
main.o:
	gcc -c main.c -o main.o
	 
clean:
	rm *.o ABB

run:
	./ABB