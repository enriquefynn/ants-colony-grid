CC=g++-4.7
CFLAGS=-O3 -std=c++0x

parser parser.cpp:
	$(CC) $(CFLAGS) parser.cpp -c
