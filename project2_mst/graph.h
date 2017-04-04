#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <stack>
#include <functional>
#include <queue>

using namespace std;

typedef char DataType;	//节点储存的数据类型
typedef double WeightType;	//边权重的数据类型
#define WEIGHT_INF 1.0/0.0

class Arc;
class Vertex;
class Graph;



/*!
 * \class Vertex
 *
 * \brief 图的节点
 *
 * \author Sky
 * \date 四月 2017
 */
class Vertex
{
	bool flagSearched;
public:
	DataType data;
	list<Arc> outArcs;
	Vertex() : flagSearched(false) {};
	Vertex(DataType dataInit);
	bool isSearched();
	void searched();
	void unSearched();
	void addAdj(Vertex& adj, WeightType w);
	void deleteAdj(Vertex& adj);
	bool operator==(Vertex const & v);
	
	friend ostream& operator<<(ostream &os, const Vertex &v);
	friend ostream& operator<<(ostream &os, const vector<Vertex *> v);
};



/*!
 * \class Arc
 *
 * \brief 图的边
 *
 * \author Sky
 * \date 四月 2017
 */
class Arc
{
public:
	double weight;
	Vertex *src, *dst;
	Arc(Vertex &s, Vertex &d, WeightType w) :
		weight(w), src(&s), dst(&d) {};
};



/*!
 * \class Graph
 *
 * \brief 图，包含增删节点、边，dfs、所有路径、mst算法
 *
 * \author Sky
 * \date 四月 2017
 */
class Graph
{
	int numVertex;
	vector<Vertex> vertexes;
	void depthFirstSearch(Vertex &v, vector<Vertex*>& depthFirstSearchRoute);
	void findAllRoute(Vertex &src, Vertex &dst);
public:
	Graph() :numVertex(0) {};
	void addVertex();
	void addVertex(DataType dataInit);
	void addDirectedArc(int src, int dst, WeightType w = 0);
	void addUndirectedArc(int src, int dst, WeightType w = 0);
	void deleteDirectedArc(int src, int dst);
	void deleteUndirectedArc(int src, int dst);
	void unSearchAll();

	void depthFirstSearch(int src, vector<Vertex*>& depthFirstSearchRoute);
	bool isConnectedDepthFirstSearch();

	void findAllRoute(int src, int dst);

	bool primMST(Graph& mst);
	struct GreaterArcPoint :greater<Arc*>
	{
		constexpr bool operator()(const Arc* _Left, const Arc* _Right) const
		{
			return (_Left->weight > _Right->weight);
		}
	};
	
	friend ostream& operator<<(ostream &os, const Graph &g);
};

