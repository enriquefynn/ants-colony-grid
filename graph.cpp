#include <iostream>
#include <sstream>
#include "graph.hpp"

using namespace std;

Graph::Graph(int x, int y)
{
}

string toStringFormat(int x, int y)
{
	string s;
	stringstream out;
	out << x << '-' << y;
	return out.str();
}

/** Inserts a node in the graph
 * \param x X coordinate
 * \param y Y coordinate
 * \param tripN The Nth trip
 * \param flags The flags for inserting node
*/
void Graph::insert(int x, int y, char direction, int tripN, int flags)
{
	string nodeStr = toStringFormat(x, y);
	//There isn't a key yet
	if (!graph.count(nodeStr))
	{
		Anode a = Anode(x, y, direction);
		graph[nodeStr] = a;
		if (whereAmI != "")
		{
			graph[whereAmI].conn.insert(&graph[nodeStr]);
			(graph[whereAmI].node)->leave();
		}
		whereAmI = nodeStr;
	}
	//There is a node with this key
	else
	{
		//Is this a new trip?
		if (flags & NEWTRIP)
		{
			(graph[whereAmI].node)->leave();
			whereAmI = nodeStr;
		}
		else
		{
			//Are we waiting in the same node?
			if (whereAmI == nodeStr)
				(graph[nodeStr].node)->wait();
			else
			{
				(graph[whereAmI].node)->leave();
				graph[whereAmI].conn.insert(&graph[nodeStr]);
				whereAmI = nodeStr;
				(graph[whereAmI].node)->enter();
			}
		}
	}
}

void Graph::print(int trips)
{
	for (auto sa : graph)
	{
		cout << sa.first << '(';
		cout << (graph[sa.first].node)->getAvgWait() << "): ";
		for (auto anode : sa.second.conn)
			cout << *(anode->node) << ' ';
		cout << endl;
	}
}








