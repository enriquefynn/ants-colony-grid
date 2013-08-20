#include <iostream>
#include "graph.hpp"

using namespace std;

Graph::Graph(int x, int y)
{
}

/** Inserts a node in the graph
 * \param x X coordinate
 * \param y Y coordinate
 * \param flags The flags for inserting node
*/
void Graph::insert(int x, int y, char direction, int flags)
{
	Node<int> node;
	node.setX(x);
	node.setY(y);
	Node<int> *nodePtr;	/*Pointer to node in fixedNodes*/
	//If there is no node in fixed yet
	if (!fixedNodes.count(node))
	{
		fixedNodes[node] = 1;
		nodePtr = (Node<int> *) &(fixedNodes.find(node)->first);
		graph[nodePtr] = unordered_set<Node<int> *>();
	}
	else
		nodePtr = (Node<int> *) &(fixedNodes.find(node)->first);
	//If node is repeated
	if ((whereTo) && (graph[whereTo].count(nodePtr)))
		++fixedNodes[node];
	else
	{
		//If there is no pointer to where insert or is a new trip just update whereTo
		if ((!whereTo) || (flags & NEWTRIP))
			goto end;
		//Add if node is not itself
		if (*whereTo != node)
			graph[whereTo].insert(nodePtr);
	}
end:
	whereTo = nodePtr;
}

void Graph::print(int trips)
{
	for (auto node : graph)
	{
		cout << *node.first << ' ';
		float totalRepetitions = 0;
		for (auto child : node.second)
			totalRepetitions+= fixedNodes[*(node.first)];
			
		for (auto child : node.second)
			cout << '(' << '"' << *child << '"' << ',' << '"' << 
			(float) fixedNodes[*(node.first)]/totalRepetitions << "\") ";
		cout << endl;
		//out << g.fixedNodes[*(node.first)];
	}
}








