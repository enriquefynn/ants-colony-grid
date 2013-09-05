#include <map>
#include <unordered_set>
#include <unordered_map>
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
};
