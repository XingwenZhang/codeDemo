#include"Floyd.h"
#include"AdjGraph.h"
#include<iostream>
using namespace std ;

int main(int argc, char** argv)
{
	//int a[6] = {INFINITY,6,1,5,INFINITY,INFINITY} ;
	//int b[6] = {6,INFINITY,5,INFINITY,3,INFINITY} ;
	//int c[6] = {1,5,INFINITY,5,6,4} ;
	//int d[6] = {5,INFINITY,5,INFINITY,INFINITY,2} ;
	//int e[6] = {INFINITY,3,6,INFINITY,INFINITY,6} ;
	//int f[6] = {INFINITY,INFINITY,4,2,6,INFINITY} ;
	//int *test[6]={a,b,c,d,e,f};
	//AdjGraph<int> adj(6,test) ;
	//adj.DFSTraverse() ;
	//cout << endl ;
	//adj.BFSTraverse() ;
	////cout << "here1" << endl ;
	//Edge<int>* tmp = Kruskal(adj) ;
	////cout << "here2" << endl ;
	//cout << endl ;
	//for(int i = 0; i < 6; i++)
	//{
	//	cout << "µÚ"<< i << "ÌõÂ· " <<tmp[i].start << "->"<<tmp[i].weight << "->"<<tmp[i].end << endl ; 
	//}
	////cout << "here3" << endl ;
	//return 0 ;

	int a[3] = {INFINITY,5,10} ;
	int b[3] = {2,INFINITY,13} ;
	int c[3] = {9,6,INFINITY} ;
	int *test[3] = {a,b,c} ;
	AdjGraph<int> TEST(3,test) ;
	int d[3] = {INFINITY,10,5} ;
	int e[3] = {9,INFINITY,6} ;
	int f[3] = {2,13,INFINITY} ;
	int *adj[3] = {d,e,f} ;
	int g[3] = {1,1,1} ;
	int h[3] = {2,2,2} ;
	int o[3] = {3,3,3} ;
	int *path[3] = {g,h,o} ;
	Floyd(TEST,adj,path) ;
	for(int i =0; i <3;i++)
		for(int j = 0; j < 3; j++)
			cout << adj[i][j] << " " ;
	return 0 ;
}