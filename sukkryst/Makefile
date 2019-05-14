NAME = ./sukkryst
SRC = ./src
GAME = ./src/game
EXTRAS = ./src/extras
OBJECTS = ./src/objects
DOC = ./doc/

COMPILER = g++
CXXFLAGS = -Wno-long-long -O0 -ggdb

all: clean compile doc

compile: 
	$(COMPILER) $(SRC)/*.cpp $(GAME)/*.cpp $(OBJECTS)/*.cpp $(EXTRAS)/*.cpp $(CXXFLAGS) -o $(NAME)

mem: 
	valgrind $(NAME)

run: 
	$(NAME)

doc: cleardoc	
	doxygen doxygen
	mv html doc

#Support
count:
	wc -l $(SRC)/*.cpp $(EXTRAS)/*.cpp $(GAME)/*.cpp $(OBJECTS)/*.cpp

countall:
	wc -l $(SRC)/*.cpp $(EXTRAS)/*.cpp $(GAME)/*.cpp $(EXTRAS)/*.h $(GAME)/*.h $(OBJECTS)/*.cpp $(OBJECTS)/*.h

clean: cleardoc clearbin clearsave

cleardoc:
	rm -fr $(DOC)

clearbin:
	rm -fr $(NAME)

clearsave:
	rm -fr ./examples/save

hello:
	echo "Makefile Check"
