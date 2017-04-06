//https://github.com/pidan1231239/project1_all_route

#include "graph.h"
#include <queue>
#include <functional>

struct GreaterDoublePoint :greater<double*>
{
	constexpr bool operator()(const double* _Left, const double* _Right) const
	{
		return (*_Left > *_Right);
	}
};

int main()
{
	//测试有向图
	Graph directedGraph;
	for (int i = 0; i < 5; i++)
	{
		directedGraph.addVertex('A' + i);
	}
	directedGraph.addDirectedArc(0, 4);
	directedGraph.addDirectedArc(4, 3);
	directedGraph.addDirectedArc(4, 1);
	directedGraph.addDirectedArc(1, 0);
	//directedGraph.addDirectedArc(1, 2);
	//directedGraph.addDirectedArc(2, 3);

	cout << "有向图的邻接链表：\n" << directedGraph;
	vector<Vertex*> depthFirstSearchRoute;
	directedGraph.depthFirstSearch(0, depthFirstSearchRoute);
	cout << "从A开始进行深度优先搜索的路径：\n" << depthFirstSearchRoute << endl;
	cout << "是否为连通图？" << directedGraph.isConnectedDepthFirstSearch() << endl;

	//cout << "从A到D的所有路径：\n";
	//directedGraph.findAllRoute(0, 3);
	//cout << "从D到A的所有路径：\n";
	//directedGraph.findAllRoute(3, 0);
	//cout << "从E到D的所有路径：\n";
	//directedGraph.findAllRoute(4, 0);


	//测试无向图
	Graph undirectedGraph;
	for (int i = 0; i < 5; i++)
	{
		undirectedGraph.addVertex('A' + i);
	}
	undirectedGraph.addUndirectedArc(0, 4);
	undirectedGraph.addUndirectedArc(4, 3);
	undirectedGraph.addUndirectedArc(4, 1);
	undirectedGraph.addUndirectedArc(1, 0);
	undirectedGraph.addUndirectedArc(1, 2);
	undirectedGraph.addUndirectedArc(2, 3);

	cout << "\n\n无向图的邻接链表：\n" << undirectedGraph;
	undirectedGraph.depthFirstSearch(0, depthFirstSearchRoute);
	cout << "从A开始进行深度优先搜索的路径：\n" << depthFirstSearchRoute << endl;
	cout << "是否为连通图？" << undirectedGraph.isConnectedDepthFirstSearch() << endl;

	//Graph mst;
	//cout << "能否找到最小生成树？" << undirectedGraph.primMST(mst) << endl;

	

	//cout << "从A到D的所有路径：\n";
	//undirectedGraph.findAllRoute(0, 3);
	//cout << "从D到A的所有路径：\n";
	//undirectedGraph.findAllRoute(3, 0);
	//cout << "从E到D的所有路径：\n";
	//undirectedGraph.findAllRoute(4, 0);


	cout << endl << "最小树测试：" << endl;
	Heap<double*, vector<double*>, GreaterDoublePoint> heapDoublePoint;
	double test[5] = {15, 5 , 6, 8, 10};
	for (int i = 0; i < 5; i++)
	{
		heapDoublePoint.push(test + i);
	}
	cout << *heapDoublePoint.top() << endl;
	//test[0] = 3;
	//对更改的节点向上冒泡
	heapDoublePoint.BubbleUpByIndex(4);

	//cout << *heapDoublePoint.top() << endl;
	//heapDoublePoint.pop();//报错，最小堆的维护失败，不能直接更改节点指向的权重
	//cout << *heapDoublePoint.top() << endl;




	return 0;
}
