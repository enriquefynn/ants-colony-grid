#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "graph.hpp"
#define nOfLines 75882909
#define NGrid 20
#define MAXMETRES 40000

using namespace std;


int main(int argc, char* argv[])
{
	char opt;
	while ((opt = getopt(argc, argv, "f")) != -1) 
	{
		switch(opt)
		{
			case 'p':
				break;
		}
	}
	
	int id, x, y;
	Graph *g = new Graph();
	int oldId = 0;
	int line = 0;
	int trips = 0;
	while(cin >> id >> x >> y)
	{
		++line;
		if (id == oldId)
			g->insert(x, y, 'E', SAMETRIP);
		else
		{
			++trips;
			g->insert(x, y, 'E', NEWTRIP);
			if (oldId+1 != id)
			{
				cout << "FILE MUST BE ORDERED at line: " << line << endl;
				cout << oldId << ' ' << id << endl;
				return 3;
			}
			oldId = id;
		}
	}
	g->print(trips);
	return 1;
}









