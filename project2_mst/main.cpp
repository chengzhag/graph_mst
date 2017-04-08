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
	////��������ͼ
	//Graph directedGraph;
	//for (int i = 0; i < 5; i++)
	//{
	//	directedGraph.addVertex('A' + i);
	//}
	//directedGraph.addDirectedArc(0, 4);
	//directedGraph.addDirectedArc(4, 3);
	//directedGraph.addDirectedArc(4, 1);
	//directedGraph.addDirectedArc(1, 0);
	//directedGraph.addDirectedArc(1, 2);
	//directedGraph.addDirectedArc(2, 3);

	//cout << "����ͼ���ڽ�����\n" << directedGraph;
	//vector<Vertex*> depthFirstSearchRoute;
	//directedGraph.depthFirstSearch(0, depthFirstSearchRoute);
	//cout << "��A��ʼ�����������������·����\n" << depthFirstSearchRoute << endl;
	//cout << "�Ƿ�Ϊ��ͨͼ��" << directedGraph.isConnectedDepthFirstSearch() << endl;

	//cout << "��A��D������·����\n";
	//directedGraph.findAllRoute(0, 3);
	//cout << "��D��A������·����\n";
	//directedGraph.findAllRoute(3, 0);
	//cout << "��E��D������·����\n";
	//directedGraph.findAllRoute(4, 0);


	////��������ͼ
	//Graph undirectedGraph;
	//for (int i = 0; i < 5; i++)
	//{
	//	undirectedGraph.addVertex('A' + i);
	//}
	//undirectedGraph.addUndirectedArc(0, 4);
	//undirectedGraph.addUndirectedArc(4, 3);
	//undirectedGraph.addUndirectedArc(4, 1);
	//undirectedGraph.addUndirectedArc(1, 0);
	//undirectedGraph.addUndirectedArc(1, 2);
	//undirectedGraph.addUndirectedArc(2, 3);

	//cout << "\n\n����ͼ���ڽ�����\n" << undirectedGraph;
	//undirectedGraph.depthFirstSearch(0, depthFirstSearchRoute);
	//cout << "��A��ʼ�����������������·����\n" << depthFirstSearchRoute << endl;
	//cout << "�Ƿ�Ϊ��ͨͼ��" << undirectedGraph.isConnectedDepthFirstSearch() << endl;

	//Graph mst;
	//cout << "�ܷ��ҵ���С��������" << undirectedGraph.primMST(mst) << endl;

	

	//cout << "��A��D������·����\n";
	//undirectedGraph.findAllRoute(0, 3);
	//cout << "��D��A������·����\n";
	//undirectedGraph.findAllRoute(3, 0);
	//cout << "��E��D������·����\n";
	//undirectedGraph.findAllRoute(4, 0);

	//������С��
	double weight[] = { 16,4,10,14,7,9,3,2,8,1 };
	Graph undirectedGraph;
	for (int i = 0; i < 10; i++)
	{
		undirectedGraph.addVertex('A' + i);
		undirectedGraph.setMinWeightArcToTree(i, 0, weight[i]);
	}
	cout << "����minHeap" << endl;
	MinHeap heap(undirectedGraph);
	cout << endl << heap;
	heap.decreaseWeight(3, 0.5);
	cout << endl << heap;
	cout << heap.empty() << endl;
	cout << heap.height() << endl;
	cout << heap.top().minWeightArcToTree.weight << endl;
	heap.pop();
	cout << endl << heap;
	cout << heap.top().minWeightArcToTree.weight << endl;
	heap.


	//cout << "\n\n����ͼ���ڽ�����\n" << undirectedGraph;
	//cout << "�Ƿ�Ϊ��ͨͼ��" << undirectedGraph.isConnectedDepthFirstSearch() << endl;



	return 0;
}
