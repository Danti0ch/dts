SRC = ../src

all: main

main: main.o vector.o array.o
	g++ main.o vector.o array.o -o main

main.o: $(SRC)/main.cpp $(SRC)/sstd.h
	g++ -c $(SRC)/main.cpp -o main.o
