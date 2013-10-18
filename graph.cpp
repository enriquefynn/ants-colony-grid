/*
 * ----------------------------------------------------------------------------
 * This software is in the BESOURO BEER-WARE LICENSE and I opted to keep it
 * as a free software, and as so, anyone who find this software useful shall
 * pay me (Enrique Fynn) <fynn@fr4c74l.com> a beer.
 * The license for this software comes in the same directory you found it
 * as LICENSE
 *
 * I prefer Weiss, IPA, or any strong brown ale. But just any beer will do.
 * ----------------------------------------------------------------------------
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "graph.hpp"

using namespace std;

/** Inserts a node in the graph
 * \param x X coordinate
 * \param y Y coordinate
 * \param tripN The Nth trip
 * \param flags The flags for inserting node
*/
void Graph::insert(SiteId<int> nodeId, int tripN, int flags)
{
	//There isn't a key yet
	if (!graph.count(nodeId))
	{
		Anode a = Anode(nodeId);
		graph[nodeId] = a;
		if (whereAmI.isValid())
		{
			graph[whereAmI].conn.insert(&graph[nodeId]);
			(graph[whereAmI].node)->leave();
		}
		whereAmI = nodeId;
	}
	//There is a node with this key
	else
	{
		//Is this a new trip?
		if (flags & NEWTRIP)
		{
			(graph[whereAmI].node)->leave();
			whereAmI = nodeId;
		}
		else
		{
			//Are we waiting in the same node?
			if (whereAmI == nodeId)
				(graph[nodeId].node)->wait();
			else
			{
				(graph[whereAmI].node)->leave();
				graph[whereAmI].conn.insert(&graph[nodeId]);
				whereAmI = nodeId;
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
pair<double, SiteId<int> > Graph::predictNext(SiteId<int> node, double maxT, double localT)
{
	if (graph[node].empty())
		return make_pair(1, node);
	if ((graph[node].node)->getAvgWait() + localT > maxT)
		return make_pair(0, node);
	double nTimes = 0;
	for (auto child : graph[node].conn)
		nTimes+= child->node->timesPassed;
	vector<pair<double, SiteId<int> > > l;
	for (auto child : graph[node].conn)
	{
		l.push_back(predictNext(child->node->getID(), maxT, localT + child->node->getAvgWait()));
		l.back().first*=(child->node->timesPassed)/nTimes;
	}
	sort(l.begin(), l.end());
	return l[0];
}

void Graph::dfs(unordered_map<SiteId<int>, bool, SiteIdHash<int>, SiteIdEqual<int> > &visited, vector<Node<SiteId<int> >* > &nodes, SiteId<int> node, double maxT, double localT)
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

vector<pair<double, SiteId<int> > > *Graph::predictNexts(SiteId<int> xy, double timeSpentHere, double maxT)
{
	vector<Node<SiteId<int> >* > probNodes = vector<Node<SiteId<int> >* >();
	unordered_map<SiteId<int>, bool, SiteIdHash<int>, SiteIdEqual<int> > visited = unordered_map<SiteId<int>, bool, SiteIdHash<int>, SiteIdEqual<int> >();
	dfs(visited, probNodes, xy, maxT, 0);
	vector<pair<double, SiteId<int> > > *probPairs = new vector<pair<double, SiteId<int> > >();
	double all = 0;
	for (auto node : probNodes)
		all+= node->timesPassed;
	for (auto node : probNodes)
		probPairs->push_back(make_pair(node->timesPassed/all, node->getID()));
	sort(probPairs->begin(),probPairs->end());
	return probPairs;
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

