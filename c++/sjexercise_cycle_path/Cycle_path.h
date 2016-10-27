#include"AdjGraph.h"
template<class EdgeType>
bool Cycle_path_helper(AdjGraph<EdgeType>& G,int v,int i,static int* & path_help,int& q)
{
	path_help[i++] = v ;
	int k = i - 1 ;
	cout << path_help[k] << " "<< v << endl ;
	Edge<EdgeType> e ;
	for(e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e))
	{
		if(e.end == q)
			return true;
		else
			Cycle_path_helper(G,e.end,i,path_help,q) ;
	}
	return false ;
}
template<class EdgeType>
void Cycle_path(AdjGraph<EdgeType>& G,int* path)
	{
		//int* path_help = new int[vertexNum] ;
		Edge<EdgeType> e ;
		int i = 0;
		int v ;
		int q ;
		int n = G.VerticesNum() ;
		bool T ;
		
		for(q = v = 0; v < n; v++)
		{
			if(q == v-1)
				i = 0 ;
			T = Cycle_path_helper(G,v,i,path,q) ;
			if(T)
				return ;
		}

}

