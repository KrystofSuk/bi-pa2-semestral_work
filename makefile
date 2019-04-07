BIN = bin/
NAME = TowerDef.out
SRC = src
UI = src/ui
DOC = doc
GAME = src/game
EXTRAS = src/extras
UI = src/ui
DOC = doc/

COMPILER = g++
FLAGSDEF = -Wno-long-long -O0 -ggdb

all: build  run 

build: 
	$(COMPILER) $(SRC)/*.cpp $(UI)/*.cpp $(GAME)/*.cpp $(EXTRAS)/*.cpp $(FLAGSDEF) -o $(BIN)$(NAME)
	cp -R res bin

mem: 
	valgrind $(BIN)$(NAME)

run: 
	$(BIN)$(NAME)

doc:
	doxygen doxygen

#Support
count:
	wc -l $(SRC)/*.cpp  $(UI)/*.cpp $(EXTRAS)/*.cpp $(GAME)/*.cpp

clear:
	rm -fr $(DOC)*
	rm -fr $(BIN)*

hello:
	echo "Makefile Check"
