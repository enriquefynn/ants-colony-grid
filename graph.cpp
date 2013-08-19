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
		graph[nodePtr] = vector<Node<int> *>();
	}
	else
		nodePtr = (Node<int> *) &(fixedNodes.find(node)->first);
	//If node is repeated
	if ((whereTo) && (!graph[whereTo].empty()) && (*graph[whereTo].back() == node))
		++fixedNodes[node];
	else
	{
		if ((!whereTo) || (flags & NEWTRIP))
			whereTo = nodePtr;
		//Add if node is not itself
		if (*whereTo != node)
		{
			graph[whereTo].push_back(nodePtr);
			whereTo = graph[whereTo].back();
		}
	}
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








