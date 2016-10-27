#ifndef KRUSKAL_H
#define KRUSKAL_H

#include"AdjGraph.h"
#include<algorithm>
#include"minheap.h"
#include"UFSets.h"
#include<cassert>

template<class EdgeType>
Edge<EdgeType>* Kruskal(AdjGraph<EdgeType>& G) 
{
	int n = G.VerticesNum() ;
	cout << "here" << n ;
	UFSets set(n) ;
	Edge<EdgeType>* MST = new Edge<EdgeType>[n-1] ;
	MinHeap<Edge<EdgeType> > H(20) ;
	Edge<EdgeType> edge ;
	for(int i = 0; i < G.VerticesNum(); i++)
	{
		for(edge = G.FirstEdge(i); G.IsEdge(edge); edge = G.NextEdge(edge))
		{
			if(G.StartVertex(edge) < G.EndVertex(edge))
			{
				H.Insert(edge) ;
			}
		}
	}
	int edgeNum = 0 ;
	while(edgeNum < n-1)

	{
		if(!H.isEmpty())
		{
			edge = H.RemoveMin() ;
			int v = edge.start ;
			int u = edge.end ;
			if(set.Find(v)!=set.Find(u))
			{
				set.Union(v,u) ;
				MST[edgeNum++]= edge ;
			}
		}
		else
		{
			assert("不存在最小生成树");
			//return ;
			exit(1) ;
		}

	}
	return MST ;
}
#endif