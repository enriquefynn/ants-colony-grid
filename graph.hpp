#include <map>
#include <vector>
#include "node.cpp"
#define SAMETRIP 0
#define NEWTRIP 1

using namespace std;

class Graph
{
	int x;
	int y;
	map<Node<int>, int> fixedNodes;
	map<Node<int> *, vector<Node<int> *> > graph;
	Node<int> *whereTo;
public:
	inline Graph(){}
	Graph(int x, int y);
	void insert(int x, int y, char direction, int flags);
	void print(int trips);
};
