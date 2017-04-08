#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <stack>
#include <float.h>
#include <math.h>


using namespace std;

class Arc;
class Vertex;
class Graph;
class MinHeap;

typedef int HeapNodeType;
typedef char DataType;	//�ڵ㴢�����������
typedef double WeightType;	//��Ȩ�ص���������

#define WEIGHT_INF DBL_MAX 

/*!
* \class Arc
*
* \brief ͼ�ı�
*
* \author Sky
* \date ���� 2017
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
 * \brief ͼ�Ľڵ�
 *
 * \author Sky
 * \date ���� 2017
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
	void setMinWeightArcToTree(Vertex *src, Vertex *dst, WeightType w = 0);
	int heapNodeIndex;
	
	friend ostream& operator<<(ostream &os, const Vertex &v);
	friend ostream& operator<<(ostream &os, const vector<Vertex *> v);
};



/*!
 * \class Graph
 *
 * \brief ͼ��������ɾ�ڵ㡢�ߣ�dfs������·����mst�㷨
 *
 * \author Sky
 * \date ���� 2017
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

	void setMinWeightArcToTree(int src, int dst, WeightType w = 0);
	bool primMST(Graph& mst);
	
	friend ostream& operator<<(ostream &os, const Graph &g);
	friend class MinHeap;
	friend ostream& operator<<(ostream &os, MinHeap &g);
};



/*!
* \class minHeap
*
* \brief ��С�ѵ�ʵ��
*
* \author Sky
* \date ���� 2017
*/
class MinHeap
{
	vector<HeapNodeType> container;
	Graph* g;
	int parent(int index);
	int left(int index);
	int right(int index);
	bool greater(int a, int b);
	void initContainer();
	void initHeapNodeIndex();
public:
	MinHeap(Graph &gInit);
	int size();
	int height();
	bool empty();
	Vertex& top();
	void upBubble(int index);
	void downBuble(int index);
	void makeHeap();
	void pop();
	void decreaseWeight(int index,WeightType w);

	friend ostream& operator<<(ostream &os, MinHeap &g);
};

