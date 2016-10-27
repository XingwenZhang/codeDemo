#include"Kruskal.h"
#include"AdjGraph.h"
#include<iostream>
using namespace std ;

int main(int argc, char** argv)
{
	int a[6] = {INFINITY,6,1,5,INFINITY,INFINITY} ;
	int b[6] = {6,INFINITY,5,INFINITY,3,INFINITY} ;
	int c[6] = {1,5,INFINITY,5,6,4} ;
	int d[6] = {5,INFINITY,5,INFINITY,INFINITY,2} ;
	int e[6] = {INFINITY,3,6,INFINITY,INFINITY,6} ;
	int f[6] = {INFINITY,INFINITY,4,2,6,INFINITY} ;
	int *test[6]={a,b,c,d,e,f};
	AdjGraph<int> adj(6,test) ;
	adj.DFSTraverse() ;
	cout << endl ;
	adj.BFSTraverse() ;
	//cout << "here1" << endl ;
	Edge<int>* tmp = Kruskal(adj) ;
	//cout << "here2" << endl ;
	cout << endl ;
	for(int i = 0; i < 6; i++)
	{
		cout << "µÚ"<< i << "ÌõÂ· " <<tmp[i].start << "->"<<tmp[i].weight << "->"<<tmp[i].end << endl ; 
	}
	//cout << "here3" << endl ;
	return 0 ;
}