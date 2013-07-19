#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <node.hpp>

#define nOfLines 75882909
#define NGrid 20
#define MAXMETRES 40000


using namespace std;

int main(int argc, char* argv[])
{
	unordered_set<node<int> > nodes;
	double NGridDiv = MAXMETRES/NGrid;

	int grid[NGrid][NGrid];
	int xi, yi;

	ifstream file(argv[1]);
	string sec, line, carID, vel, aux;
	vector<pair<node<int>*, int times> > keep;
	double x, y;
	//int i = 0;
	node<int> auxNode = new node<int>(0, 0, 'E');
	int ntimes = 0;
	while(getline(file, line)) 
	{
		stringstream ss(line);
		ss >> sec >> carID;

		ss >> aux;
		xi = stod(aux)/NGridDiv;
		
		ss >> aux;
		yi = stod(aux)/NGridDiv;

		ss >> vel;
		auxNode.setX(xi);
		auxNode.setY(yi);
		auxNode.setDirection('E');
		//cout << i++ << endl;
		auto no = nodes.find(auxNode);
		if (no == NULL)
			nodes.insert(auxNode);
		if (keep.size() > 1)
		{
			if (no == keep.back())
				++ntimes;
			else
			{
				no.setDirection(keep.back().getDirection(node));
				ntimes = 0;
			}
		}
		if (no == keep.back())
		
		
		keep.insert(make_pair(no,
		if (!v.first.empty())
		{
			if 
			if ((v[v.size()-1].first) != xi || (v[v.size()-1].second != yi))
				routes[carID].push_back(make_pair(xi, yi));
		}
		else
			routes[carID].push_back(make_pair(xi, yi));
		//cout << sec << ' ' << carID << ' ' << xi << ' ' << yi << ' ' << v << endl;
	}
	for (auto l : routes)
	{
		cout << l.first;
		for (auto r : l.second)
				cout << r.first << '.'<< r.second << ' ';
		cout << endl;
	}
	
	return 1;
}
