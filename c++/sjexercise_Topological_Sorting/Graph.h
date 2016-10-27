//#ifndef GRAPH_H
//#define GRAPH_H
//#include<>
//class Graph
//{
//private:
//
//
//};
//
//
//
//
//int visited[MAX_VERTEX_NUM] ;
//void dfs_trave(ALGraph alg)
//{
//	int i ;
//	for(i = 0; i < alg.vexnum; i++)
//	{
//		visited[i] = 0 ;
//	}
//	for(i=0; i < alg.vexnum; i++)
//	{
//		if(visited[i] = 0)
//			dfs(alg,i) ;
//	}
//}
//
//void dfs(ALGraph alg, int i)
//{
//	visist(i) ;
//	visited[i] = i ;
//	ARCNODE *p = alg.vextices[i].firstarc ;
//	while(p!=NULL)
//	{
//		if(visited[p->adjvex] == 0)
//		{
//			dfs(alg,p->adjvex) ;
//		}
//		p = p->nextarc ;
//	}
//}
//#endif

#ifndef GRAPH_H
#define GRAPH_H
#include<queue>
#include<limits>
#include<iostream>
using namespace std ;
const int UNVISITED = 0 ;
const int VISITED = 1 ;
const int INFINITY = INT_MAX ;
void visit(int v)
{
	cout << v<<"->" ;
}
template<class EdgeType>
class Edge
{
public:
	int start, end ;
	int weight;
	Edge() 
	{
		start = end = 0 ;
		weight = 0; 
	}

	Edge(int st, int en, int w) 
	{
		start = st ;
		end = en ;
		weight = w ;
	}
	bool operator < (Edge<EdgeType> temp)
	{
		if(this->weight < temp.weight)
			return true ;
		else
			return false ;
	}
	bool operator > (Edge<EdgeType> temp)
	{
		if(this->weight > temp.weight)
			return true ;
		else
			return false ;
	}
};

template<class EdgeType>
class Graph
{
public:
	int vertexNum ;
	int edgeNum ;
	int *Mark ;
	Graph(int verticesNum)
	{
		vertexNum = verticesNum ;
		edgeNum = 0 ;
		Mark = new int[vertexNum] ;
		for(int i = 0; i < vertexNum; i++)
		{
			Mark[i] = UNVISITED ;
		}

	}

	~Graph()
	{
		delete [] Mark ;
		//delete [] Indegree ;
	}

	virtual Edge<EdgeType> FirstEdge(int oneVertex) = 0 ;
	virtual Edge<EdgeType> NextEdge(Edge<EdgeType> oneEdge) = 0 ;
	int VerticesNum()
	{
		return vertexNum ;
	}
	int EdgesNum()
	{
		return edgeNum;
	}
	bool IsEdge(Edge<EdgeType> oneEdge)
	{
		if(oneEdge.weight > 0 && oneEdge.weight < INFINITY && oneEdge.end >= 0)
			return true ;
		else
			return false ;
	}
	int StartVertex(Edge<EdgeType> oneEdge)
	{
		return oneEdge.start ;
	}
	int EndVertex(Edge<EdgeType> oneEdge)
	{
		return oneEdge.end ;
	}
	EdgeType Weight(Edge<EdgeType> oneEdge)
	{
		return oneEdge.weight ;
	}
	virtual void setEdge(int start, int end, int weight) = 0 ;
	virtual void delEdge(int start, int end) = 0 ;
	void BFS(int v) ;
	void BFSTraverse() ;
	void DFS(int v) ;
	void DFSTraverse() ;
};
template<class EdgeType>
void Graph<EdgeType>::BFS(int v)
{
	//int u ;
	queue<int> Q ;
	Mark[v] = VISITED ;
	visit(v) ;
	Q.push(v) ;
	while(!Q.empty())
	{
		//v = Q.front() ;
		Q.pop() ;
		for(Edge<EdgeType> e = FirstEdge(v); IsEdge(e); e = NextEdge(e))
		{
			int u = Mark[EndVertex(e)] ;
			if(Mark[u] == UNVISITED)
			{
				visit(u) ;
				Mark[u] = VISITED ;
				Q.push(u) ;
			}
		}
	}
}
template<class EdgeType>
void Graph<EdgeType>::BFSTraverse()
{
	int v ;
	for(v = 0; v < VerticesNum(); v++)
	{
		Mark[v] = UNVISITED ;
	}
	for(v = 0; v < VerticesNum(); v++)
	{
		if(Mark[v] == UNVISITED)
			BFS(v);
	}
}

template<class EdgeType>
void Graph<EdgeType>::DFS(int v)
{
	Mark[v] = VISITED ;
	visit(v) ;
	Edge<EdgeType> e ;
	for(e = FirstEdge(v); IsEdge(e); e = NextEdge(e))
	{
		if(Mark[this->EndVertex(e)] == UNVISITED)    //ÐÞ¸Ä
			DFS(EndVertex(e)) ;
	}
}
template<class EdgeType>
void Graph<EdgeType>::DFSTraverse()
{
	for(int i = 0; i < VerticesNum(); i++)
	{
		Mark[i] = UNVISITED ;
	}
	for(int i = 0; i < VerticesNum(); i++)
	{
		if(Mark[i] == UNVISITED)
			DFS(i) ;
	}
}


#endif