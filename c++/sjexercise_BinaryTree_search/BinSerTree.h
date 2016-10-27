#ifndef BINSERTREE_H
#define BINSERTREE_H
#include"BinSerTreeNode.h"
template<class T>
class BinSerTree
{
public:
	BinSerTreeNode<T> *root ;
	BinSerTreeNode<T>* search(BinSerTreeNode<T>* root,T key) ;
	void insert(const T& key) ;
	void remove(BinSerTreeNode<T>*& node) ;
	BinSerTree():root(NULL){}
	void inorder(BinSerTreeNode<T>*) ;
};

template<class T>
BinSerTreeNode<T>* BinSerTree<T>::search(BinSerTreeNode<T>* root , T key)
{
	while((root->data != key) && (root != NULL))
	{
		if(root->data > key)
		{
			root = root->left ;
		}
		else
		{
			root = root->right ;
		}
	}
	return root ;
}
	
template<class T>
void BinSerTree<T>::insert(const T& key)
{
	BinSerTreeNode<T> *p = root, *prev = NULL ;
	while(p!=NULL)
	{
		prev = p ;
		
		if(key < p->data)
		{
			p = p->left ;
		}
		else
		{
			p = p->right ;
		}
	}
	if(root == NULL)
	{
		root = new BinSerTreeNode<T>(key) ;
	}
	else if(key < prev->data)
	{
		p = prev->left = new BinSerTreeNode<T>(key) ;
		p->parent = prev ;
		//p->parent->left = p ;
		p->tag = 0 ;                                   //left child is 0
	}
	else 
	{
		p = prev->right = new BinSerTreeNode<T>(key) ;
		p->parent = prev ;
		//p->parent->right = p ;
		p->tag = 1 ;
	}
}

template<class T>
void BinSerTree<T>::remove(BinSerTreeNode<T>*& node)
{
	BinSerTreeNode<T>* p = NULL ;
	BinSerTreeNode<T>* tmp = node ;
	if(node != NULL)
	{
		if(!node->right)
		{
			if(node->tag)
				node->parent->right = node->left ;
			else
				node->parent->left = node->left ;
			node = node->left ;
		}
		else if(!node->left)
		{
			if(node->tag)
				node->parent->right = node->right ;
			else
				node->parent->left = node->left ;
			node = node->right ;
		}
		else
		{
			tmp = node->left ;
			while(tmp->right)
				tmp = tmp->right ;
			if(node->tag)
				node->parent->right = node->left ;
			else
				node->parent->left = node->left ;
			tmp->right = node->right ;
			tmp = node ;
			node = node->left ;
		}
		delete tmp ;
	}
	//if node is null, do nothing
}

template<class T>
void BinSerTree<T>::inorder(BinSerTreeNode<T>* root)
{
	if(root != NULL)
	{
		inorder(root->left) ;
		cout << root->data << endl ;
		inorder(root->right) ;
	}

}
#endif
