#include <iostream>
#include "graph.hpp"

using namespace std;

Graph::Graph(int x, int y)
{
}

/** Inserts a node in the graph
 * \param x X coordinate
 * \param y Y coordinate
 * \param flags The flags for inserting
*/
void Graph::insert(int x, int y, char direction, int flags)
{
	Node<int> node;
	node.setX(x);
	node.setY(y);
	Node<int> *nodePtr;
	if (!fixedNodes.count(node))
	{
		fixedNodes[node] = 0;
		nodePtr = (Node<int> *) &(fixedNodes.find(node)->first);
		graph[nodePtr] = vector<Node<int> *>();
	}
	else
		nodePtr = (Node<int> *) &(fixedNodes.find(node)->first);
	//If node is repeated
	if ((!graph[nodePtr].empty()) && (*graph[nodePtr].back() == node))
		++fixedNodes[node];
	else
	{
		if ((!whereTo) || (flags & NEWTRIP))
			whereTo = nodePtr;
		graph[whereTo].push_back(nodePtr);
		whereTo = graph[whereTo].back();
	}
}

void Graph::print()
{
	for (auto node : fixedNodes)
		cout << node.first << ' ' << node.second << endl;
}
