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
	double xd, yd;
	int id, x, y;
	Graph *g = new Graph();
	int oldId = 0;
	int line = 0;
	int trips = 1;
	string nodePredicted = "-1--1";
	double probability = 0;
	string b;
	int time, oldTime = 0;
	getline(cin, b);
	vector<pair<double, string> > *p;
	while(cin >> xd >> yd >> b >> id >> time) {
		x = xd*1000;
		y = yd*1000;
		if (time - oldTime < 80)
		{
			for (auto pprob : *p)
			{
				if (pprob.second == toFormat(x, y))
				{
					nodePredicted = pprob.second;
					probability = pprob.first;
				}
			}
			if (nodePredicted != "-1--1")
				cout << probability << endl;
			else
				cout << 0 << endl;
		}
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
		p = g->predictNext(x, y, 0, 1);
		//cout << "At " << toFormat(x, y) << " probability " << probability << " to " << nodePredicted << endl;
		oldTime = time;
	}
	if (testFlag)
		while(cin >> id >> x >> y)
		{
			
		}
	g->print(trips);
	return 0;
}









