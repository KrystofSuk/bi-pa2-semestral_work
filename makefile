BIN = sukkryst/
NAME = TowerDef.out
SRC = src
UI = src/ui
GAME = src/game
EXTRAS = src/extras
UI = src/ui
DOC = doc/

COMPILER = g++
CXXFLAGS = -Wno-long-long -O0 -ggdb

all: clear compile doc

compile: 
	mkdir -p $(BIN)
	$(COMPILER) $(SRC)/*.cpp $(UI)/*.cpp $(GAME)/*.cpp $(EXTRAS)/*.cpp $(CXXFLAGS) -o $(BIN)$(NAME)

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
	rm -fr $(DOC)
	rm -fr $(BIN)

hello:
	echo "Makefile Check"
