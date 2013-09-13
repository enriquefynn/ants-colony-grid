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

#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "node.cpp"
#define SAMETRIP 0
#define NEWTRIP 1

using namespace std;

struct Anode
{
	Node<int> *node;
	unordered_set<const Anode *> conn;
	Anode(int x, int y, char d)
	{
		node = new Node<int>(x, y, d);
	}
	Anode() {}
	inline bool empty() {return conn.empty();}
};

class Graph
{
	unordered_map<string, Anode > graph;	/*The Graph*/
	string whereAmI;
public:
	inline Graph(){}
	Graph(int x, int y);
	void insert(int x, int y, char direction, int tripN, int flags);
	void print(int trips);
	vector<pair<double, string> > *predictNext(int x, int y, double timeSpentHere, double maxT);
	void dfs(unordered_map<string, bool> &visited, vector<Node<int >* > &nodes, string node, double maxT, double localT);
	pair<double, string> predictNext(string node, double maxT, double localT);
};
