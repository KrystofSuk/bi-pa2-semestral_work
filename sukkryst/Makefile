NAME = ./sukkryst
SRC = ./src
GAME = ./src/game
EXTRAS = ./src/extras
DOC = ./doc/

COMPILER = g++
CXXFLAGS = -Wno-long-long -O0 -ggdb

all: clean compile doc

compile: 
	$(COMPILER) $(SRC)/*.cpp $(GAME)/*.cpp $(EXTRAS)/*.cpp $(CXXFLAGS) -o $(NAME)

mem: 
	valgrind $(NAME)

run: 
	$(NAME)

doc: cleardoc	
	doxygen doxygen
	mv html doc

#Support
count:
	wc -l $(SRC)/*.cpp   $(EXTRAS)/*.cpp $(GAME)/*.cpp

clean: cleardoc clearbin

cleardoc:
	rm -fr $(DOC)

clearbin:
	rm -fr $(NAME)

hello:
	echo "Makefile Check"
