#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
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

/** Predict where to be
 * \param node Node
 * \param maxT Maximum forecast time
 * \param localT Local time (for recursion)
*/
pair<double, string> Graph::predictNext(string node, double maxT, double localT)
{
	if (graph[node].empty())
		return make_pair(1, node);
	if ((graph[node].node)->getAvgWait() + localT > maxT)
		return make_pair(0, node);
	double nTimes = 0;
	for (auto child : graph[node].conn)
		nTimes+= child->node->timesPassed;
	vector<pair<double, string > > l;
	for (auto child : graph[node].conn)
	{
		l.push_back(predictNext(child->node->getID(), 
								maxT, localT + child->node->getAvgWait()));
		l.back().first*=(child->node->timesPassed)/nTimes;
	}
	sort(l.begin(), l.end());
	return l[0];
}

void Graph::dfs(unordered_map<string, bool> &visited, vector<Node<int >* > &nodes, string node, double maxT, double localT)
{
	if (visited[node] == true)
		return;
	visited[node] = true;
	if ((graph[node].node)->getAvgWait() + localT > maxT)
	{
		nodes.push_back(graph[node].node);
		return;
	}
	if (graph[node].empty())
		return;
	for (auto child : graph[node].conn)
	{
		dfs(visited, nodes, child->node->getID(), maxT, localT + child->node->getAvgWait());
	}
}

pair<double, string> Graph::predictNext(int x, int y, double timeSpentHere, double maxT)
{
	string xy = toStringFormat(x, y);
	vector<Node<int>* > probNodes = vector<Node<int>* >();
	unordered_map<string, bool> visited = unordered_map<string, bool>();
	dfs(visited, probNodes, xy, maxT, 0);
	int i = 0;
	int best = 0;
	double bestT = 0;
	double all = 0;
	for (auto node : probNodes)
	{
		int timeP = node->timesPassed;
		all+= timeP;
		if (timeP > bestT)
		{
			bestT = timeP;
			best = i;
		}
		++i;
	}
	if (!all)
		return make_pair(0, "-1--1");
	return make_pair(probNodes[best]->timesPassed/all, probNodes[best]->getID());
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

