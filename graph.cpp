#include "node.hpp"
#include "graph.hpp"

template <typename T>
void Graph<T>::insert(T x, T y, char dir)
{
	Node<T> node;
	node.setX(x);
	node.setY(y);
	node.setDirection(dir);
	
	if (node == root)
		whereTo = &root;
	else
	{	
		if (!fixedNodes.count(node))
		{
			fixedNodes[node] = 0;
			graph[node] = vector<Node<T> *>();
		}
		vector<Node<T> *> v = graph[node];
		if ((v.size() > 0) && (node == &whereTo))
			++fixedNodes[&whereTo];
		else
		{
			Node<T> *nodePtr = &fixedNodes.find(node);
			graph[&whereTo].push_back(nodePtr);
			whereTo = nodePtr;
		}
	}
}

