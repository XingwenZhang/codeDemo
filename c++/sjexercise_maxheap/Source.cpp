#include<iostream>
#include"maxheap.h"
using namespace std ;

int main(int argc, char** argv)
{
	int a,b;
	int t[20];
	for(int i=0; i < 20; i++)
	{
		t[i] = i ;
	}
	MaxHeap<int> M(t,10,20);
	M.BuildHeap();
	M.show();
	cout<<"insert£º"<<endl;
	cin>>a;
	M.Insert(a);
	M.show();
	cout<<"delete£º"<<endl;
	cin>>b;
	M.Remove(b);
	M.show();
	cout<<"removemax "<<endl;
	M.RemoveMax();
	M.show();
	return 0 ;
}