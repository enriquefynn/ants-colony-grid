#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <iostream>

#define nOfLines 75882909
#define NGrid 20
#define MAXMETRES 40000

using namespace std;

class node
{
	double x;
	double y;
	char direction;
	public:
	inline node(double x, double y) { this->x = x; this->y = y;}
	inline friend bool operator== (const node& lhs, const node& rhs){return ((lhs.direction == rhs.direction) && (lhs.x == rhs.x) && (lhs.y == rhs.y));}
	inline friend bool operator< (const node& lhs, const node& rhs){ return (lhs.x == rhs.x) ? (lhs.y < rhs.y): (lhs.x < rhs.x);}
};

int main(int argc, char* argv[])
{
	double NGridDiv = MAXMETRES/NGrid;

	int grid[NGrid][NGrid];
	int xi, yi;

	ifstream file(argv[1]);
	string sec, line, carID, vel, aux;
	set<pair<node*, int times> > keep;
	double x, y;
	//int i = 0;
	while(getline(file, line)) 
	{
		stringstream ss(line);
		ss >> sec >> carID;

		ss >> aux;
		xi = stod(aux)/NGridDiv;
		
		ss >> aux;
		yi = stod(aux)/NGridDiv;

		ss >> vel;
		//cout << i++ << endl;
		auto v = routes[carID];
		if (!v.empty())
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
