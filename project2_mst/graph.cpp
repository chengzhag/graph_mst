#include "graph.h"

/*函数实现*/

ostream& operator<<(ostream & os, const Vertex & v) {
	os << v.data << " -> ";
	list<Vertex*>::const_iterator it;
	for (it = v.adjvex.begin(); it != v.adjvex.end(); it++)
	{
		os << (**it).data << " , ";
	}
	return os;
}


ostream& operator<<(ostream & os, const vector<Vertex*> v) {
	vector<Vertex*>::const_iterator it;
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


bool Vertex::operator==(Vertex const & v)
{
	return this == &v;
}


void Vertex::deleteAdj(Vertex& adj)
{
	list<Vertex*>::iterator it;

	for (it = adjvex.begin(); it != adjvex.end();)
	{
		if (*it == &adj)
		{
			adjvex.erase(it);
			break;
		}
	}
}


void Vertex::addAdj(Vertex& adj)
{
	adjvex.push_back(&adj);
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


void Graph::addUndirectedArc(int src, int dst)
{
	addDirectedArc(src, dst);
	addDirectedArc(dst, src);
}


void Graph::unSearchAll()
{
	vector<Vertex>::iterator it;
	for (it = vertexes.begin(); it != vertexes.end(); it++)
	{
		(*it).unSearched();
	}
}


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
	list<Vertex*>::iterator it;
	for (it = src.adjvex.begin(); it != src.adjvex.end(); it++)
	{
		if (!(*it)->isSearched())
		{
			findAllRoute(**it, dst);
			(*it)->unSearched();
		}
	}
	searchRoute.pop_back();
}


void Graph::findAllRoute(int src, int dst)
{
	unSearchAll();
	findAllRoute(vertexes[src], vertexes[dst]);
}

//递归实现

void Graph::depthFirstSearch(Vertex &v)
{
	v.searched();
	cout << v.data;
	list<Vertex*>::iterator it;
	for (it = v.adjvex.begin(); it != v.adjvex.end(); it++)
	{
		if (!(*it)->isSearched())
		{
			depthFirstSearch(**it);
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


void Graph::addDirectedArc(int src, int dst)
{
	vertexes[src].addAdj(vertexes[dst]);
}


void Graph::addVertex()
{
	vertexes.push_back(Vertex());
	numVertex++;
}