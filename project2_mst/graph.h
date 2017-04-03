#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <stack>

using namespace std;


template<class C>
class Vertex
{
	bool flagSearched;
public:
	C data;
	list<Vertex<C>*> adjvex;
	Vertex() : flagSearched(false) {};
	Vertex(C dataInit);
	bool isSearched();
	void searched();
	void unSearched();
	void addAdj(Vertex<C>& adj);
	void deleteAdj(Vertex<C>& adj);
	bool operator==(Vertex const & v);
	template<class C>
	friend ostream& operator<<(ostream & os, const Vertex<C> & v);
};

template<class C>
ostream& operator<<(ostream & os, const Vertex<C> & v) {
	os << v.data << " -> ";
	list<Vertex<C>*>::const_iterator it;
	for (it = v.adjvex.begin(); it != v.adjvex.end(); it++)
	{
		os << (**it).data << " , ";
	}
	return os;
}

template<class C>
ostream& operator<<(ostream & os, const vector<Vertex<C>*> v) {
	vector<Vertex<C>*>::const_iterator it;
	for (it = v.begin(); it != v.end(); it++)
	{
		os << (*it)->data;
	}
	return os;
}

template<class C>
void Vertex<C>::unSearched()
{
	flagSearched = false;
}

template<class C>
bool Vertex<C>::operator==(Vertex<C> const & v)
{
	return this == &v;
}

template<class C>
void Vertex<C>::deleteAdj(Vertex<C>& adj)
{
	list<Vertex<C>*>::iterator it;

	for (it = adjvex.begin(); it != adjvex.end();)
	{
		if (*it == &adj)
		{
			adjvex.erase(it);
			break;
		}
	}
}

template<class C>
void Vertex<C>::addAdj(Vertex<C>& adj)
{
	adjvex.push_back(&adj);
}

template<class C>
Vertex<C>::Vertex(C dataInit)
{
	data = dataInit;
	flagSearched = false;
}

template<class C>
bool Vertex<C>::isSearched()
{
	return flagSearched;
}

template<class C>
void Vertex<C>::searched()
{
	flagSearched = true;
}


template<typename T, class C>
class Arc
{
public:
	T weight;
	Vertex<C>* dst;
	Arc(T w, Vertex<C>* d) :weight(w), dst(d) {};
};


template<class C>
class Graph
{
	int numVertex;
	vector<Vertex<C>> vertexes;
	void depthFirstSearch(Vertex<C> &v);
	void findAllRoute(Vertex<C> &src, Vertex<C> &dst);
public:
	Graph() :numVertex(0) {};
	void addVertex();
	void addVertex(C dataInit);
	void addDirectedArc(int src, int dst);
	void addUndirectedArc(int src, int dst);
	void deleteDirectedArc(int src, int dst);
	void deleteUndirectedArc(int src, int dst);
	void unSearchAll();
	void depthFirstSearch(int src);
	void findAllRoute(int src, int dst);
	template<class C>
	friend ostream& operator<<(ostream &os, const Graph<C> &g);
};

template<class C>
void Graph<C>::deleteUndirectedArc(int src, int dst)
{
	deleteDirectedArc(src, dst);
	deleteDirectedArc(dst, src);
}

template<class C>
void Graph<C>::addUndirectedArc(int src, int dst)
{
	addDirectedArc(src, dst);
	addDirectedArc(dst, src);
}

template<class C>
void Graph<C>::unSearchAll()
{
	vector<Vertex<C>>::iterator it;
	for (it = vertexes.begin(); it != vertexes.end(); it++)
	{
		(*it).unSearched();
	}
}

template<class C>
void Graph<C>::findAllRoute(Vertex<C> &src, Vertex<C> &dst)
{
	static vector<Vertex<C>*> searchRoute;
	src.searched();
	searchRoute.push_back(&src);
	//cout << src.data;
	if (src == dst)
	{
		cout << searchRoute << endl;
		searchRoute.pop_back();
		return;
	}
	list<Vertex<C>*>::iterator it;
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

template<class C>
void Graph<C>::findAllRoute(int src, int dst)
{
	unSearchAll();
	findAllRoute(vertexes[src], vertexes[dst]);
}

//µ›πÈ µœ÷
template<class C>
void Graph<C>::depthFirstSearch(Vertex<C> &v)
{
	v.searched();
	cout << v.data;
	list<Vertex<C>*>::iterator it;
	for (it = v.adjvex.begin(); it != v.adjvex.end(); it++)
	{
		if (!(*it)->isSearched())
		{
			depthFirstSearch(**it);
		}
	}
}

template<class C>
void Graph<C>::depthFirstSearch(int src)
{
	unSearchAll();
	depthFirstSearch(vertexes[src]);
}

template<class C>
void Graph<C>::deleteDirectedArc(int src, int dst)
{
	vertexes[src].deleteAdj(vertexes[dst]);
}

template<class C>
ostream& operator<<(ostream &os, const Graph<C> &g) {
	vector<Vertex<C>>::const_iterator it;
	for (it = g.vertexes.begin(); it != g.vertexes.end(); it++)
	{
		cout << *it << endl;
	}
	return os;
}

template<class C>
void Graph<C>::addVertex(C dataInit)
{
	vertexes.push_back(Vertex<C>(dataInit));
	numVertex++;
}

template<class C>
void Graph<C>::addDirectedArc(int src, int dst)
{
	vertexes[src].addAdj(vertexes[dst]);
}

template<class C>
void Graph<C>::addVertex()
{
	vertexes.push_back(Vertex<C>());
	numVertex++;
}