CC=g++-4.7
CCFLAGS=-O3 -std=c++0x -march=native

all: parser.o node.o graph.o
	$(CC) $(CCFLAGS) node.o graph.o parser.o -o main
parser.o: parser.cpp
	$(CC) $(CCFLAGS) -c parser.cpp
node.o: node.cpp
	$(CC) $(CCFLAGS) -c node.cpp
graph.o: graph.cpp graph.hpp
	$(CC) $(CCFLAGS) -c graph.cpp
clean:
	rm -Rf *.o main
