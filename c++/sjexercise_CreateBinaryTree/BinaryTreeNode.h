#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H

#include<iostream>
using namespace std ;

template<class T>
class BinaryTreeNode
{
public:
	T m_data ;
	BinaryTreeNode<T> *m_leftChild ;
	BinaryTreeNode<T> *m_rightChild ;

	BinaryTreeNode():m_leftChild(NULL) , m_rightChild(NULL){};
	BinaryTreeNode(const T &data, BinaryTreeNode<T> *leftChild=NULL, BinaryTreeNode<T> *rightChild=NULL):m_data(data),
		m_leftChild(leftChild), m_rightChild(rightChild) {};
	T& getData()
	{
		return m_data ;
	}
	BinaryTreeNode<T> *getLeftChild()
	{
		return m_leftChild ;
	}
	BinaryTreeNode<T> *getRightChlid()
	{
		return m_rightChild ;
	}
	void SetData(const T& data)
	{
		m_data = data ;
	}
	void SetLeftChild(BinaryTreeNode<T> *leftChild)
	{
		m_leftChild = leftChild ;
	}
	void SetRightChild(BinaryTreeNode<T> *rightChild)

	{
		m_rightChild = rightChild ;
	}
};
#endif