#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <stack>

using namespace std;

typedef char DataType;	//�ڵ㴢�����������
typedef double weightType;	//��Ȩ�ص���������

class Arc;
class Vertex;
class Graph;



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
	Vertex() : flagSearched(false) {};
	Vertex(DataType dataInit);
	bool isSearched();
	void searched();
	void unSearched();
	void addAdj(Vertex& adj, weightType w);
	void deleteAdj(Vertex& adj);
	bool operator==(Vertex const & v);
	
	friend ostream& operator<<(ostream &os, const Vertex &v);
	friend ostream& operator<<(ostream &os, const vector<Vertex *> v)
};



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
	Arc(Vertex &s, Vertex &d, weightType w) :
		weight(w), src(&s), dst(&d) {};
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
	void depthFirstSearch(Vertex &v);
	void findAllRoute(Vertex &src, Vertex &dst);
public:
	Graph() :numVertex(0) {};
	void addVertex();
	void addVertex(DataType dataInit);
	void addDirectedArc(int src, int dst, weightType w = 0);
	void addUndirectedArc(int src, int dst, weightType w = 0);
	void deleteDirectedArc(int src, int dst);
	void deleteUndirectedArc(int src, int dst);
	void unSearchAll();

	vector<Vertex*> depthFirstSearch(int src);
	vector<Vertex*> depthFirstSearchRoute;

	void findAllRoute(int src, int dst);
	
	friend ostream& operator<<(ostream &os, const Graph &g);
};

