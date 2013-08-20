#include <map>
#include <unordered_set>
#include "node.cpp"
#define SAMETRIP 0
#define NEWTRIP 1

using namespace std;

class Graph
{
	map<Node<int>, int> fixedNodes;	/*Fixed nodes:avg waiting*/
	map<Node<int> *, unordered_set<Node<int> *> > graph;	/*The Graph*/
	Node<int> *whereTo;
public:
	inline Graph(){}
	Graph(int x, int y);
	void insert(int x, int y, char direction, int flags);
	void print(int trips);
};
