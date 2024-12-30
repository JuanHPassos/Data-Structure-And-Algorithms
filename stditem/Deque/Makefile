all: Embaralhar.o item.o Deque.o
	gcc item.o Deque.o Embaralhar.o -std=c99 -o embaralhar -Wall

Embaralhar.o:
	gcc -c Embaralhar.c -o Embaralhar.o

Deque.o:
	gcc -c Deque.c -o Deque.o

item.o:
	gcc -c item.c -o item.o
clean:
	rm *.o embaralhar
run:
	./embaralhar < exemplo.in