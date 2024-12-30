all: mainitem.o item.o PilhaSEQ.o
	gcc item.o PilhaSEQ.o mainitem.o -std=c99 -o mainitem -Wall

mainitem.o:
	gcc -c mainitem.c -o mainitem.o

PilhaSEQ.o:
	gcc -c PilhaSEQ.c -o PilhaSEQ.o

item.o:
	gcc -c item.c -o item.o
clean:
	-rm *.o mainitem
run:
	./mainitem