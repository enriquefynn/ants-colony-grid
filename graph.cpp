#include <iostream>
#include "graph.hpp"

using namespace std;

Graph::Graph(int x, int y)
{
}

/** Inserts a node in the graph
 * \param x X coordinate
 * \param y Y coordinate
 * \param tripN The Nth trip
 * \param flags The flags for inserting node
*/
void Graph::insert(int x, int y, char direction, int tripN, int flags)
{
	Node<int> node;
	node.setX(x);
	node.setY(y);
	Node<int> *nodePtr;	/*Pointer to node in fixedNodes*/
	//If there is no node in fixed yet
	if (!fixedNodes.count(node))
	{
		node.setAvgWait(1.);
		fixedNodes[node] = 1;
		nodePtr = (Node<int> *) &(fixedNodes.find(node)->first);
		graph[nodePtr] = unordered_set<Node<int> *>();
	}
	else
		nodePtr = (Node<int> *) &(fixedNodes.find(node)->first);
	//If node is repeated
	if ((whereTo) && graph[whereTo].count(nodePtr))
	{
		++fixedNodes[node];
		cout << "F: " << fixedNodes[node] << endl;
	}
	else
	{
		//If for some reason has no where to go, end
		if (!whereTo)
			goto end;
		//If it is a new trip update average time
		if (flags & NEWTRIP)
		{
			((*fixedNodes.find(node)).first).setAvgWait((node.getAvgWait() + fixedNodes[node])/tripN);
			fixedNodes[node] = 1;
			goto end;
		}
		//Add if node is not itself
		if (*whereTo != node)
			graph[whereTo].insert(nodePtr);
		else
		{
			++fixedNodes[node];
			cout << "F: " << fixedNodes[node] << endl;
		}
	}
end:
	whereTo = nodePtr;
	cout << "WHERE: " << *whereTo << endl;
}

void Graph::print(int trips)
{
	for (auto node : graph)
	{
		cout << *node.first << ' ';
		for (auto child : node.second)
			cout << '(' << '"' << *child << '"' << ',' << '"' << 
			child->getAvgWait() << "\") ";
		cout << endl;
		//out << g.fixedNodes[*(node.first)];
	}
}








