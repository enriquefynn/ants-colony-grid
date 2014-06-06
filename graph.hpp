#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "node.cpp"
#define SAMETRIP 0
#define NEWTRIP 1

using namespace std;

struct Anode
{
	Node<SiteId<int> > *node;
	unordered_set<const Anode *> conn;
	Anode(SiteId<int> id, int tripID)
	{
		node = new Node<SiteId<int> >(id, tripID);
	}

	~Anode()
	{
		//delete node;
	}

	Anode() {}
	inline bool empty() {return conn.empty();}
};

class Graph
{
	unordered_map<SiteId<int>, Anode, SiteIdHash<int>, SiteIdEqual<int> > graph;	/*The Graph*/
	SiteId<int> whereAmI;
public:
	inline Graph(){}
	void insert(SiteId<int> id, int tripN, int flags);
	void print(int trips);
	vector<pair<double, SiteId<int> > > *predictNexts(SiteId<int> id, double timeSpentHere, double maxT, int tripID);
	pair<double, SiteId<int> >          predictNext(SiteId<int> id, double maxT, double localT);
	void dfs(unordered_map<SiteId<int>, bool, SiteIdHash<int>, SiteIdEqual<int> > &visited, vector<Node<SiteId<int> >* > &nodes, SiteId<int> node, double maxT, double localT);
};
