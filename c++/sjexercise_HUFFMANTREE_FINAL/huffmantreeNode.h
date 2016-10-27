#ifndef HUFFMANTREENODE_H
#define HUFFMANTREENODE_H
#include<iostream>
#include<map>
#include<string>
#include<fstream>


template<class T>
class HuffmanTreeNode
{
public:
	HuffmanTreeNode<T> *parent, *lchild, *rchild ;
	double element ;                                      //weight
	T data ;
	bool operator > (HuffmanTreeNode<T> temp)
	{
		if(this->element > temp.element)
			return true ;
		else
			return false ;
	}
	HuffmanTreeNode()
	{
		parent = NULL ;
		lchild = NULL ;
		rchild = NULL ;
		element = 0.0 ;
	}
	HuffmanTreeNode(const HuffmanTreeNode<T>& temp)
	{
		this->data = temp.data ;
		this->element = temp.element ;
		this->lchild = temp.lchild ;
		this->rchild = temp.rchild ;
		this->parent = temp.parent ;
	}
};


#endif