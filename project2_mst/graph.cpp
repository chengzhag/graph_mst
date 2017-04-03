#include "graph.h"


ostream& operator<<(ostream &os, const Vertex &v) {
	os << v.data << " -> ";
	list<Arc>::const_iterator it;
	for (it = v.outArcs.begin(); it != v.outArcs.end(); it++)
	{
		os << "(" << (*it).weight << ")" << (*it).dst->data << " , ";
	}
	return os;
}


ostream& operator<<(ostream &os, const vector<Vertex *> v) {
	vector<Vertex *>::const_iterator it;
	for (it = v.begin(); it != v.end(); it++)
	{
		os << (*it)->data;
	}
	return os;
}


void Vertex::unSearched()
{
	flagSearched = false;
}


bool Vertex::operator==(Vertex const &v)
{
	return this == &v;
}


void Vertex::deleteAdj(Vertex &adj)
{
	list<Arc>::iterator it;

	for (it = outArcs.begin(); it != outArcs.end();)
	{
		if ((*it).dst == &adj)
		{
			outArcs.erase(it);
			break;
		}
	}
}


void Vertex::addAdj(Vertex &adj,weightType w)
{
	outArcs.push_back(Arc(*this, adj, w));
}


Vertex::Vertex(DataType dataInit)
{
	data = dataInit;
	flagSearched = false;
}


bool Vertex::isSearched()
{
	return flagSearched;
}


void Vertex::searched()
{
	flagSearched = true;
}


void Graph::deleteUndirectedArc(int src, int dst)
{
	deleteDirectedArc(src, dst);
	deleteDirectedArc(dst, src);
}


void Graph::addUndirectedArc(int src, int dst, weightType w)
{
	addDirectedArc(src, dst, w);
	addDirectedArc(dst, src, w);
}


void Graph::unSearchAll()
{
	vector<Vertex>::iterator it;
	for (it = vertexes.begin(); it != vertexes.end(); it++)
	{
		(*it).unSearched();
	}
}


//************************************
// Method:    findAllRoute
// FullName:  Graph::findAllRoute
// Description: 找到从src到dst之间的所有路径
//						改自dfs算法
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Vertex & src
// Parameter: Vertex & dst
//************************************
void Graph::findAllRoute(Vertex &src, Vertex &dst)
{
	static vector<Vertex*> searchRoute;
	src.searched();
	searchRoute.push_back(&src);
	//cout << src.data;
	if (src == dst)
	{
		cout << searchRoute << endl;
		searchRoute.pop_back();
		return;
	}
	list<Arc>::iterator it;
	for (it = src.outArcs.begin(); it != src.outArcs.end(); it++)
	{
		if (!(*it).dst->isSearched())
		{
			findAllRoute(*(*it).dst, dst);
			(*it).dst->unSearched();
		}
	}
	searchRoute.pop_back();
}


void Graph::findAllRoute(int src, int dst)
{
	unSearchAll();
	findAllRoute(vertexes[src], vertexes[dst]);
}


//************************************
// Method:    depthFirstSearch
// FullName:  Graph::depthFirstSearch
// Description: 深度优先算法，递归实现
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Vertex & v
//************************************
void Graph::depthFirstSearch(Vertex &v)
{
	v.searched();
	cout << v.data;
	list<Arc>::iterator it;
	for (it = v.outArcs.begin(); it != v.outArcs.end(); it++)
	{
		if (!(*it).dst->isSearched())
		{
			depthFirstSearch(*(*it).dst);
		}
	}
}


void Graph::depthFirstSearch(int src)
{
	unSearchAll();
	depthFirstSearch(vertexes[src]);
}


void Graph::deleteDirectedArc(int src, int dst)
{
	vertexes[src].deleteAdj(vertexes[dst]);
}


ostream& operator<<(ostream &os, const Graph &g) {
	vector<Vertex>::const_iterator it;
	for (it = g.vertexes.begin(); it != g.vertexes.end(); it++)
	{
		cout << *it << endl;
	}
	return os;
}


void Graph::addVertex(DataType dataInit)
{
	vertexes.push_back(Vertex(dataInit));
	numVertex++;
}


void Graph::addDirectedArc(int src, int dst,weightType w)
{
	vertexes[src].addAdj(vertexes[dst], w);
}


void Graph::addVertex()
{
	vertexes.push_back(Vertex());
	numVertex++;
}