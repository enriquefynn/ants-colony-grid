#include "node.hpp"

unordered_set<node<int> > fixed_nodes;
class graph
{
	vector<pair<node<int>*, int times> > path;
	node<int> *aux = new node<int>(0, 0, 'E');
	int repeat = 0;
	
	void insert(int x, int y)
	{
		aux.setX(x);
		aux.setY(y);
		auto tryNode = nodes.find(auxNode);
		if (tryNode == NULL)
			fixed_nodes.insert(aux);
		if (path.size() > 1)
		{
			if (aux == path.back())
				path.
		}
	}
}
