#include "graph.h"

ostream& operator<<(ostream &os, const Vertex &v) {
	os << v.data << " -> ";
	list<Arc>::const_iterator it;
	for (it = v.outArcs.begin(); it != v.outArcs.end(); it++)
	{
		os << "(" <<it->weight << ")" << it->dst->data << " , ";
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

ostream& operator<<(ostream &os, const Graph &g) {
	vector<Vertex>::const_iterator it;
	for (it = g.vertexes.begin(); it != g.vertexes.end(); it++)
	{
		cout << *it << endl;
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
		if (it->dst == &adj)
		{
			outArcs.erase(it);
			break;
		}
	}
}


void Vertex::addAdj(Vertex &adj,WeightType w)
{
	outArcs.push_back(Arc(this, &adj, w));
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


void Graph::addUndirectedArc(int src, int dst, WeightType w)
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
		if (!it->dst->isSearched())
		{
			findAllRoute(*(it->dst), dst);
			it->dst->unSearched();
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
void Graph::depthFirstSearch(Vertex &v, vector<Vertex*>& depthFirstSearchRoute)
{
	v.searched();
	depthFirstSearchRoute.push_back(&v);
	//cout << v.data;
	list<Arc>::iterator it;
	for (it = v.outArcs.begin(); it != v.outArcs.end(); it++)
	{
		if (!it->dst->isSearched())
		{
			depthFirstSearch(*(it->dst), depthFirstSearchRoute);
		}
	}
}


void Graph::depthFirstSearch(int src, vector<Vertex*>& depthFirstSearchRoute)
{
	unSearchAll();
	depthFirstSearchRoute.clear();
	depthFirstSearch(vertexes[src], depthFirstSearchRoute);
}


bool Graph::isConnectedDepthFirstSearch()
{
	vector<Vertex*> depthFirstSearchRoute;
	depthFirstSearch(0, depthFirstSearchRoute);
	return depthFirstSearchRoute.size() == vertexes.size();
}

//************************************
// Method:    primMST
// FullName:  Graph::primMST
// Description: 基于Prim算法的MST函数
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: Graph & mst
//************************************

//priority_queue<double, vector<Arc*>, Graph::GreaterArcPoint> heapArcToTree;
//Arc a(*Vertex(), *Vertex(), 4);
//Arc b(*Vertex(), *Vertex(), 3);
//Arc c(*Vertex(), *Vertex(), 6);
//Arc d(*Vertex(), *Vertex(), 5);
//heapArcToTree.push(&a);
//cout << heapArcToTree.top()->weight << endl;
//heapArcToTree.push(&b);
//cout << heapArcToTree.top()->weight << endl;
//heapArcToTree.push(&c);
//cout << heapArcToTree.top()->weight << endl;
//heapArcToTree.push(&d);
//cout << heapArcToTree.top()->weight << endl;
//heapArcToTree.pop();
//cout << heapArcToTree.top()->weight << endl;

bool Graph::primMST(Graph& mst)
{
	//以priority_queue储存到树的最小权重边
	if (!isConnectedDepthFirstSearch())
	{
		return false;
	} 



	return true;
}

void Graph::deleteDirectedArc(int src, int dst)
{
	vertexes[src].deleteAdj(vertexes[dst]);
}





void Graph::addVertex(DataType dataInit)
{
	vertexes.push_back(Vertex(dataInit));
	numVertex++;
}


void Graph::addDirectedArc(int src, int dst,WeightType w)
{
	vertexes[src].addAdj(vertexes[dst], w);
}


void Graph::addVertex()
{
	vertexes.push_back(Vertex());
	numVertex++;
}



int MinHeap::parent(int index)
{
	return (index - 1) / 2;
}

int MinHeap::left(int index)
{
	return index * 2+1;
}

int MinHeap::right(int index)
{
	return index * 2 + 2;
}

bool MinHeap::greater(HeapNodeType a, HeapNodeType b)
{
	return a->minWeightArcToTree.weight>b->minWeightArcToTree.weight;
}

int MinHeap::size()
{
	return container.size();
}

bool MinHeap::empty()
{
	return container.empty();
}

HeapNodeType MinHeap::top()
{
	return container.front();
}

void MinHeap::upBubble(int index)
{
	int i = index;
	while (i > 1 && container[parent(i)] > container[i])
	{
		swap(container[i]->heapNodeIndex, container[parent(i)]->heapNodeIndex);
		swap(container[i], container[parent(i)]);
		i = parent(i);
	}
	
}

void MinHeap::downBuble(int index)
{
	int l = left(index);
	int r = right(index);
	int min;
	if (l < size() && greater(container[index], container[l]))
	{
		min = l;
	}
	if (r < size() && greater(container[min], container[r]))
	{
		min = r;
	}
	if (min != index)
	{
		swap(container[min]->heapNodeIndex, container[index]->heapNodeIndex);
		swap(container[min], container[index]);
		downBuble(min);
	}
}

void MinHeap::makeHeap()
{
	int length = size() / 2 - 1;
	for (int i = length; i >= 0; i--)
	{
		downBuble(i);
	}
}

void MinHeap::pop()
{
	container[0] = container[size() - 1];
	container.pop_back();
	downBuble(0);
}

void MinHeap::decreaseWeight(int index, WeightType w)
{
	if (w < container[index]->minWeightArcToTree.weight)
	{
		container[index]->minWeightArcToTree.weight = w;
		upBubble(index);
	}
}
