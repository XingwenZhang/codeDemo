#ifndef FLOYD_H
#define FLOYD_H
#include"AdjGraph.h"
#include"Graph.h"

template<class EdgeType>
void Floyd(AdjGraph<EdgeType>& G, EdgeType **Adj, int** Path)
{
	int i , j, v ;
	int n = G.VerticesNum() ;
	/*for(i = 0; i < n; i++)
	{
		for(j = 0; j < n ;j++)
		{
			if(i == j)
			{
				Adj[i][j] = INFINITY ;
				Path[i][j] = i ;
			}
			else
			{
				Adj[i][j] = INFINITY ;
				Path[i][j] = -1 ;
			}
		}
	}*/
	for(v = 0; v < n; v++)
	{
		for(Edge<EdgeType> e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e))
		{
			Adj[v][e.end] = G.Weight(e) ;
		}
	}
	for(v = 0; v < n; v++)
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if(Adj[i][j] > (Adj[i][v]+Adj[v][j]) )
				{
					Adj[i][j] = Adj[i][v] + Adj[v][j] ;
					Path[i][j] = v ;
				}
}

#endif