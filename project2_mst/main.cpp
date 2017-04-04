//https://github.com/pidan1231239/project1_all_route

#include "graph.h"
#include <queue>
#include <functional>


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

	Graph mst;
	//cout << "能否找到最小生成树？" << undirectedGraph.primMST(mst) << endl;

	

	//cout << "从A到D的所有路径：\n";
	//undirectedGraph.findAllRoute(0, 3);
	//cout << "从D到A的所有路径：\n";
	//undirectedGraph.findAllRoute(3, 0);
	//cout << "从E到D的所有路径：\n";
	//undirectedGraph.findAllRoute(4, 0);


	return 0;
}
