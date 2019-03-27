all: build mem run

build:
	g++ ./src/main.cpp ./src/ui.cpp -Wall -pedantic -o ./bin/o.out -O2 
mem: build
	valgrind ./bin/o.out
run: build
	./bin/o.out
hello:
	echo "Makefile Right"
