all: main.o circulo.o ponto.o
	gcc ponto.o circulo.o main.o -std=c99 -o distancia -Wall -lm

main.o:
	gcc -c main.c -o main.o

circulo.o:
	gcc -c circulo.c -o circulo.o

ponto.o:
	gcc -c ponto.c -o ponto.o
clean:
	rm *.o distancia
run:
	./distancia