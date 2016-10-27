#include"graph.h"
int main(){
	Graph<int,int> g(5);
	for(int i = 0;i < 5;i++){
		g.InsertVertex(i);
	}
	//初始化图
	g.InsertEdge(0,1,10);
	g.InsertEdge(1,2,50);
	g.InsertEdge(3,2,20);
	g.InsertEdge(3,4,30);
	g.InsertEdge(0,3,30);
	g.InsertEdge(2,4,10);
	g.InsertEdge(0,4,100);
	//cout << "原始有向图：" << endl;
	//g.Cout();

	int startVertexValue = 0;
	int numVertex = g.GetNumVertex();
	int *DijkstraPath = g.Dijkstra(startVertexValue);
	cout << "\t";
	for(int i = 0;i < numVertex;i++)
		cout << "\t" << i;
	cout << endl;
	cout << "\t" << startVertexValue;
	for(int i = 0;i < numVertex;i++)
		cout << "\t" <<DijkstraPath[i] ;
	return 0;
}