BIN = ./bin/
NAME = TowerDef.out
SRC = src
DOC = doc

COMPILER = g++
FLAGSDEF = -Wall -pedantic -O2

all: builddef  run 

builddef: 
	$(COMPILER) $(SRC)/*.cpp $(FLAGSDEF) -o $(BIN)$(NAME)  

mem: 
	valgrind $(BIN)$(NAME)

run: 
	$(BIN)$(NAME)

#Support
countrows:
	wc -l $(SRC)/*.cpp

clearbin:
	rm $(BIN)*

hello:
	echo "Makefile Check"
