#include"Topological_Sorting.h"

#include<iostream>
using namespace std ;


int main(int argc, char** argv)
{
	int a[3] = {INFINITY,5,10} ;
	int b[3] = {2,INFINITY,13} ;
	int c[3] = {9,6,INFINITY} ;
	int *test[3] = {a,b,c} ;
	AdjGraph<int> TEST(3,test) ;
	int* sortarray = new int[100] ;
	sortarray[0] = 123 ;
	bool t = TopologySort(TEST,sortarray) ;
	if(t)
		cout << "work" << endl ;
	else
		cout << "false" << endl ;
	//cout << sortarray[0] << endl ;
	/*for(int i =0; i <3;i++)
		for(int j = 0; j < 3; j++)
			cout << adj[i][j] << " " ;*/
	return 0 ;
}