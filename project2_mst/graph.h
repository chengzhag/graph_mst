#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <stack>
#include <float.h>


using namespace std;

class Arc;
class Vertex;
class Graph;
class MinHeap;

typedef Vertex* HeapNodeType;
typedef char DataType;	//节点储存的数据类型
typedef double WeightType;	//边权重的数据类型

#define WEIGHT_INF DBL_MAX 

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
	Arc(Vertex *s, Vertex *d, WeightType w) :
		weight(w), src(s), dst(d) {};
};


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
	Vertex() : flagSearched(false), minWeightArcToTree(this, NULL, WEIGHT_INF) {};
	Vertex(DataType dataInit) :flagSearched(false), minWeightArcToTree(this, NULL, WEIGHT_INF), data(dataInit) {};
	bool isSearched();
	void searched();
	void unSearched();
	void addAdj(Vertex& adj, WeightType w);
	void deleteAdj(Vertex& adj);
	bool operator==(Vertex const & v);

	Arc minWeightArcToTree;
	int heapNodeIndex;
	
	friend ostream& operator<<(ostream &os, const Vertex &v);
	friend ostream& operator<<(ostream &os, const vector<Vertex *> v);
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
	
	friend ostream& operator<<(ostream &os, const Graph &g);
};



/*!
* \class minHeap
*
* \brief 最小堆的实现
*
* \author Sky
* \date 四月 2017
*/
class MinHeap
{
	vector<HeapNodeType> container;
	int parent(int index);
	int left(int index);
	int right(int index);
	bool greater(HeapNodeType a, HeapNodeType b);
public:
	MinHeap(vector<HeapNodeType>& data) :
		container(data) {
		makeHeap();
	};
	int size();
	bool empty();
	HeapNodeType top();
	void upBubble(int index);
	void downBuble(int index);
	void makeHeap();
	void pop();
	void decreaseWeight(int index,WeightType w);
};

