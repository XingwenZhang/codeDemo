#include"AdjGraph.h"
#include<iostream>

using namespace std ;
template<class EdgeType>
bool TopologySort(AdjGraph<EdgeType>& G, int* SortArray)
{
	int n = G.VerticesNum() ;
	int* indegree = new int[n] ;
	int v ;
	Edge<EdgeType> e ;
	for(v = 0; v < n; v++) //³õÊ¼»¯
	{
		indegree[v] = 0 ;
		G.Mark[v] = UNVISITED ;
	}
	for(v = 0; v < n; v++)
	{
		for(e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e))
		{
			indegree[e.end]++ ;
		}
	}
	for(int i = 0; i < n; i++)
	{
		for(v = 0; v < n; v++)
		{
			if(indegree[v] == 0 && G.Mark[v] == UNVISITED)
			{
				break ;
			}
		}
		if(v == n)
		{
			return false ;
		}
		G.Mark[v] = VISITED ;
		SortArray[i] = v ;
		for(e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e))
		{
			indegree[e.end]-- ;
		}
	}
	delete [] indegree ;
	return true ;
}