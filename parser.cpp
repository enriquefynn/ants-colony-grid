#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <string>
#include "graph.hpp"
#include "graph.cpp"
#define nOfLines 75882909
#define NGrid 20
#define MAXMETRES 40000


using namespace std;

int main(int argc, char* argv[])
{
	double NGridDiv = MAXMETRES/NGrid;

	int grid[NGrid][NGrid];
	int xi, yi;

	ifstream file(argv[1]);
	string sec, line, carID, vel, aux;
	double x, y;
	
	//First time is the root node;
	getline(file, line);
	stringstream ss(line);
	ss >> sec >> carID;

	ss >> aux;
	xi = stod(aux)/NGridDiv;
	
	ss >> aux;
	yi = stod(aux)/NGridDiv;

	ss >> vel;
	
	Graph<int> *g = new Graph<int>(xi, yi);
	
	while(getline(file, line)) 
	{
		ss >> sec >> carID;

		ss >> aux;
		xi = stod(aux)/NGridDiv;
		
		ss >> aux;
		yi = stod(aux)/NGridDiv;

		ss >> vel;
		g->insert(xi, yi, 'E');
	}
	return 1;
}









