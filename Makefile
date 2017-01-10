EXEC=sfml-app
SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)
SFML=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system 
CCFLAGS=-Wall -g --std=c++11
CC=g++

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(SFML)
%.o: %.cc
	$(CC) $(CCFLAGS) -c $< -o $@ 

.depend:
	g++ -MM $(SOURCES) > .depend
-include .depend
clean:
	rm -f $(OBJECTS) $(EXEC)

test:
	./sfml-app
