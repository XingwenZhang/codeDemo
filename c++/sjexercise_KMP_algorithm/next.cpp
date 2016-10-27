#include<string>
#include<iostream>
#include<assert.h>
#include<iterator>
using namespace std ;
int* mynext(string p)
{
	int m = p.size() ;
	assert(m>0) ;
	int *N = new int[m] ;
	assert(N != 0) ;
	N[0] = 0 ;
	for(int i = 1; i < m ; i++)
	{
		int k = N[i-1] ;
		while(k > 0 && p[i] != p[k])
			k = N[k-1] ;
		if(p[i]==p[k])
			N[i] = k+ 1 ;
		else
			N[i] = 0 ;
	}
	return N ;
}