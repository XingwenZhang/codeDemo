#include"MinHeap.h"
#include<iostream>
using namespace std ;

int main(int argc, char** argv)

{
	//char p[10] = {'a','b','c','d','e','f','g','h','i','j'} ;
	char p[10] = {'t','w','a','r','l','q','x','b','s','o'};
	char c ;
	MinHeap<char> minheap1(10) ;
	for(int i = 0;i < 10; i++)
	{
		minheap1.Insert(p[i]) ;
	}
	//minheap1.show() ;
	for(int i = 0; i < 10 ; i++)
	{
		
	c = minheap1.RemoveMin() ;
	cout << c ;
	}
	cout << minheap1.CurrentSize << endl ;

	minheap1.show() ;
	minheap1.Insert('o') ;
	minheap1.show() ;
	return 0 ;
}