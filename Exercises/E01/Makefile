all: Cliente.o circulo.o ponto.o
	gcc ponto.o circulo.o Cliente.o -std=c99 -o pon_circ -Wall

Cliente.o:
	gcc -c Cliente.c -o Cliente.o

circulo.o:
	gcc -c circulo.c -o circulo.o

ponto.o:
	gcc -c ponto.c -o ponto.o
clean:
	rm *.o pon_circ
run:
	./pon_circ