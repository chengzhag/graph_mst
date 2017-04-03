#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <stack>

using namespace std;

typedef char DataType;
typedef double weightType;

class Arc;
class Vertex;
class Graph;


/*ÀàÉùÃ÷*/
class Vertex
{
	bool flagSearched;
public:
	DataType data;
	list<Vertex*> adjvex;
	Vertex() : flagSearched(false) {};
	Vertex(DataType dataInit);
	bool isSearched();
	void searched();
	void unSearched();
	void addAdj(Vertex& adj);
	void deleteAdj(Vertex& adj);
	bool operator==(Vertex const & v);
	
	friend ostream& operator<<(ostream & os, const Vertex & v);
};

class Arc
{
public:
	double weight;
	Vertex* dst;
	Arc(double w, Vertex* d) :weight(w), dst(d) {};
};

class Graph
{
	int numVertex;
	vector<Vertex> vertexes;
	void depthFirstSearch(Vertex &v);
	void findAllRoute(Vertex &src, Vertex &dst);
public:
	Graph() :numVertex(0) {};
	void addVertex();
	void addVertex(DataType dataInit);
	void addDirectedArc(int src, int dst);
	void addUndirectedArc(int src, int dst);
	void deleteDirectedArc(int src, int dst);
	void deleteUndirectedArc(int src, int dst);
	void unSearchAll();
	void depthFirstSearch(int src);
	void findAllRoute(int src, int dst);
	
	friend ostream& operator<<(ostream &os, const Graph &g);
};

