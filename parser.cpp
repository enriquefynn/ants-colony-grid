#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include "graph.hpp"
#define nOfLines 75882909
#define NGrid 20
#define MAXMETRES 40000


using namespace std;

int main(int argc, char* argv[])
{
	int id, x, y;
	Graph *g = new Graph(9, 4);
	int oldId = 0;
	int line = 0;
	while(cin >> id >> x >> y)
	{
		++line;
		if (id == oldId)
			g->insert(x, y, 'E', SAMETRIP);
		else
		{
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
	g->print();
	return 1;
}









