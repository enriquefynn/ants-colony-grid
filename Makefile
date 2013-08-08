CC=g++-4.6
CCFLAGS=-O3 -std=c++0x

all: parser.o node.o
	$(CC) $(CCFLAGS) node.o parser.o -o main
parser.o: parser.cpp
	$(CC) $(CCFLAGS) -c parser.cpp
node.o: node.cpp node.hpp
	$(CC) $(CCFLAGS) -c node.cpp
clean:
	rm -Rf *.o main
