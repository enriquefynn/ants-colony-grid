/*
 * ----------------------------------------------------------------------------
 * This software is in the BESOURO BEER-WARE LICENSE and I opted to keep it
 * as a free software, and as so, anyone who find this software useful shall
 * pay me (Enrique Fynn) <fynn@fr4c74l.com> a beer.
 * The license for this software comes in the same directory you found it
 * as LICENSE
 *
 * I prefer Weiss, IPA, or any strong brown ale. But just any beer will do.
 * ----------------------------------------------------------------------------
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include "graph.hpp"
#define nOfLines 75882909
#define NGrid 20
#define MAXMETRES 40000

using namespace std;

string toFormat(int x, int y)
{
  string s;
  stringstream out;
  out << x << '-' << y;
  return out.str();
}

int main(int argc, char* argv[])
{
	char opt;
	int testLine;
	bool testFlag = false;
	while ((opt = getopt(argc, argv, "t:h")) != -1) 
	{
		switch(opt)
		{
			case 't':
				testLine = stoi(optarg);
				break;
			case 'h':
			default:
				puts("Receives the input from stdin\nOptions:\n\t-t <line>: Begin to test from <line> inclusive till EOF");
				exit(1);
		}
	}
	
	int id, x, y;
	Graph *g = new Graph();
	int oldId = 0;
	int line = 0;
	int trips = 1;
	string nodePredicted = "-1--1";
	double probability = 0;
	while(cin >> id >> x >> y)
	{
		if (nodePredicted == toFormat(x, y))
			cout << probability << endl;
		else
			cout << 0 << endl;
		++line;
		if (testFlag && (line == testLine))
			break;
		if (id == oldId)
			g->insert(x, y, 'E', trips, SAMETRIP);
		else
		{
			++trips;
			g->insert(x, y, 'E', trips, NEWTRIP);
			if (oldId+1 != id)
			{
				cerr << "FILE MUST BE ORDERED at line: " << line << '\n'
				<< oldId << ' ' << id << endl;
				return 3;
			}
			oldId = id;
		}
		pair<double, string> p = g->predictNext(x, y, 0, 1);
		nodePredicted = p.second;
		probability = p.first;
		//cout << "At " << toFormat(x, y) << " probability " << probability << " to " << nodePredicted << endl;
	}
	if (testFlag)
		while(cin >> id >> x >> y)
		{
			
		}
	g->print(trips);
	return 0;
}









