#ifndef PRIM_H
#define PRIM_H
#include"AdjGraph.h"
#include<vector>
#include<algorithm>
template<class EdgeType>
Edge<EdgeType>* Prim(AdjGraph<EdgeType>& G, int s)
{
	int min = INFINITY ;
	int index= -1 ;
	int k = 0;
	int n = G.VerticesNum() ;
	vector<int> vertex ;
	vector<int> cmp ;
	vector<vector<int> > nearweight ;
	Edge<EdgeType> *path ;
	path = new Edge<EdgeType>[n] ;
	vertex.push_back(s) ;
	
	vector<int> tmpweight ;
	/*for(e = G.FirstEdge(s); G.IsEdge(e); e = G.NextEdge(e))
	{
		static int m = 0;

	}*/
	//把权值全部读入
	for(int i = 0; i<n; i++)
	{
		for(int j=0;j<n;j++)
		{
			tmpweight.assign(G.matrix[j],G.matrix[j]+n) ;
			nearweight.push_back(tmpweight) ;
		}
	}
	//找到权值最小的点
	for(int m = 0; m < n; m++)
	{
		int tmp = vertex.size();
		for(int i = 0; i < tmp; i++)
		{
			tmpweight = nearweight[vertex[i]] ;
			sort(tmpweight.begin(),tmpweight.end()) ;
			if(tmpweight[0] < min)
			{
				min = tmpweight[0] ;
				index = i ;
			}
			
		}
		vector<int>::iterator it ;
		it = find(nearweight[vertex[index]].begin(),nearweight[vertex[index]].end(),min) ;
		int q = it - nearweight[vertex[index]].begin() ;
		vector<int>::iterator it2 ;
		it2 = find(vertex.begin(), vertex.end(),q) ;
		if(it2 == vertex.end())
		{
		vertex.push_back(it - nearweight[vertex[index]].begin()) ;
		//cout <<  vertex.back() ;
		nearweight[vertex[index]][vertex.back()] = INFINITY ;
		nearweight[vertex.back()][vertex[index]] = INFINITY ;
		
		//储存权值最小的边
		Edge<EdgeType> e(vertex[index],vertex[k+1],min) ;
		min = INFINITY ;
		path[k++] = e ;
		}
		else
		{
			nearweight[vertex[index]][vertex.back()] = INFINITY ;
			nearweight[vertex.back()][vertex[index]] = INFINITY ;
			min = INFINITY ;
		}

	}
	return path ;
}

#endif