#ifndef BINSERTREENODE_H
#define BINSERTREENODE_H
#include<iostream>

template<class T>
class BinSerTreeNode
{
public:
	BinSerTreeNode<T> *left ;
	BinSerTreeNode<T> *right ;
	T data ;
	char tag ;
	BinSerTreeNode<T> *parent ;
	BinSerTreeNode(T data) 
	{
		left = NULL ;
		right = NULL ;
		parent = NULL ;
		tag = 0 ;
		this->data = data ;
	}
};
#endif