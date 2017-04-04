//https://github.com/pidan1231239/project1_all_route

#include "graph.h"
#include <queue>
#include <functional>


int main()
{
	Graph directedGraph;
	for (int i = 0; i < 5; i++)
	{
		directedGraph.addVertex('A' + i);
	}
	directedGraph.addDirectedArc(0, 4);
	directedGraph.addDirectedArc(4, 3);
	directedGraph.addDirectedArc(4, 1);
	directedGraph.addDirectedArc(1, 0);
	directedGraph.addDirectedArc(1, 2);
	directedGraph.addDirectedArc(2, 3);
	cout << "����ͼ���ڽ�����\n" << directedGraph;
	vector<Vertex*> depthFirstSearchRoute;
	directedGraph.depthFirstSearch(0, depthFirstSearchRoute);
	cout << "��A��ʼ�����������������·����\n" << depthFirstSearchRoute << endl;
	cout << "��A��D������·����\n";
	directedGraph.findAllRoute(0, 3);
	cout << "��D��A������·����\n";
	directedGraph.findAllRoute(3, 0);
	cout << "��E��D������·����\n";
	directedGraph.findAllRoute(4, 0);

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
	cout << "\n\n����ͼ���ڽ�����\n" << undirectedGraph;
	undirectedGraph.depthFirstSearch(0, depthFirstSearchRoute);
	cout << "��A��ʼ�����������������·����\n" << depthFirstSearchRoute << endl;
	cout << "��A��D������·����\n";
	undirectedGraph.findAllRoute(0, 3);
	cout << "��D��A������·����\n";
	undirectedGraph.findAllRoute(3, 0);
	cout << "��E��D������·����\n";
	undirectedGraph.findAllRoute(4, 0);

	//priority_queue<double, vector<double>, greater<double>> heap;
	//for (int i = 0; i < 10; i++)
	//{
	//	heap.push(i);
	//}
	//cout << endl;
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << heap.top()<<" ";
	//	heap.pop();
	//}

	return 0;
}
