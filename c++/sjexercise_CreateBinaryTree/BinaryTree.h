#ifndef BINARYTREE_H
#define BINARYTREE_H
#include"BinaryTreeNode.h"
#include<queue>
#include<stack>
#include<string>

template<class T>
class BinaryTree
{
private:
	 BinaryTreeNode<T> *m_root ;
public:
	BinaryTree() : m_root(NULL) {} ;
	BinaryTree(T data) 
	{
		m_root = new BinaryTreeNode<T>(data) ;
	};
	virtual ~BinaryTree() ;

	bool IsEmpty() const
	{
		return m_root == NULL ? true:false ;
	};
	bool IsLeftChild(BinaryTreeNode<T> *p)
	{
		return p == getParent(p)->getLeftChild() ? true : false ;
	};
	bool IsRightChild(BinaryTreeNode<T> *p)
	{
		return p == getParent(p)->getRightChild() ? true : false ;
	};
	BinaryTreeNode<T> * &getRoot()
	{
		return m_root ;
	};
	BinaryTreeNode<T> *getParent(BinaryTreeNode<T> *p)
	{
		return Parent(m_root, p) ;
	};
	BinaryTreeNode<T> *LeftChild(BinaryTreeNode<T> *root) const
	{
		return root == NULL ? NULL : root->getLeftChild() ;
	};
	BinaryTreeNode<T> *RightChild(BinaryTreeNode<T> *root) const
	{
		return root == NULL ? NULL : root->getRightChild() ;
	};
	BinaryTreeNode<T> *LeftSibling(BinaryTreeNode<T> *leftChild) ;
	BinaryTreeNode<T> *RightSibling(BinaryTreeNode<T> *rightChild) ;
	T Retrieve(BinaryTreeNode<T> *p) const
	{
		return p->getData() ;
	};
	void Assign(BinaryTreeNode<T> *p, const T &d) const 
	{
		p->SetData(d) ;
	};
//	void InsertRoot(BinaryTreeNode<T> *p, const T &d) ;
	void InsertLeftChild(BinaryTreeNode<T> *p, const T &d) const ;
	void InsertRightChild(BinaryTreeNode<T> *p, const T &d) const ;
	void DeleteLeftChild(BinaryTreeNode<T> *p)
	{
		Destroy(p->getLeftChild()) ;
	};
	void DeleteRightChild(BinaryTreeNode<T> *p)
	{
		Destroy(p->getRightChlid()) ;
	};
	void PreOrderTraverse(BinaryTreeNode<T> *root) const ;
    void InOrderTraverse(BinaryTreeNode<T> *root) const ;
    void PostOrderTraverse(BinaryTreeNode<T> *root) const ;
	virtual void LevelOrderTraverse(BinaryTreeNode<T> *root) const ;
	void createBinTreePre(BinaryTreeNode<T>* &tree, string pre, string mid) ;
	void createBinTreePost(BinaryTreeNode<T>* &tree, string mid, string post);
protected :
	BinaryTreeNode<T> *Parent(BinaryTreeNode<T> *root, BinaryTreeNode<T> *p) ;
	void Destroy(BinaryTreeNode<T> *p) ;
};

template<class T>
BinaryTree<T>::~BinaryTree()
{
	Destroy(m_root) ;
	m_root = NULL ;
}
template<class T>
BinaryTreeNode<T> *BinaryTree<T>::RightSibling(BinaryTreeNode<T> *p)
{
	BinaryTreeNode<T> *q ;
	q = Parent(m_boot, p) ;
	if((q == NULL) || (p == q->getRightChlid()))
	{
		return NULL ;
	}
	else
	{
		return q->getRightChlid() ;
	}
}
template<class T>
BinaryTreeNode<T> *BinaryTree<T>::LeftSibling(BinaryTreeNode<T> *p)
{
	BinaryTreeNode<T> *q ;
	q = Parent(m_root, p) ;
	if((q == NULL) || (p == q->getLeftChild()))
		return NULL ;
	else
		return q->getLeftChild() ;

}
template<class T>
void BinaryTree<T>::InsertLeftChild(BinaryTreeNode<T> *p, const T &d) const 
{
	BinaryTreeNode<T> *q = new BinaryTreeNode<T>(d) ;
	q->SetLeftChild(p->getLeftChild() ) ;                 //插入旧树时使用
	p->SetLeftChild(q) ;
}
template<class T>
void BinaryTree<T>::InsertRightChild(BinaryTreeNode<T> *p, const T &d) const
{
	BinaryTreeNode<T> *q = new BinaryTreeNode<T>(d) ;
	q->SetRightChild(p->getRightChlid()) ;
	p->SetRightChild(q) ;
}
template<class T>
void BinaryTree<T>::Destroy(BinaryTreeNode<T> *p)
{
	if(p != NULL)
	{
		Destroy(p -> getLeftChild()) ;
		Destroy(p -> getRightChlid()) ;
		delete p ;
	}
}

template<class T>
BinaryTreeNode<T> *BinaryTree<T>::Parent(BinaryTreeNode<T> *root, BinaryTreeNode<T> *p)
{
	BinaryTreeNode<T> *q ;
	if(root == NULL)
		return NULL ;
	else if((p == root->getLeftChild())|| (p == root->getRightChlid()))
	{
		return root ;
	}
	else if((q = Parent(root->getLeftChild(), p)) != NULL)
		return q ;
	else if
		return Parent (root->getRightChlid(), p) ;
}

template<class T>
void BinaryTree<T>::LevelOrderTraverse(BinaryTreeNode<T> *root) const 
{
	queue<BinaryTreeNode<T> *> q ;
	if (root != NULL)
		q.push(root) ;
	while(!q.empty())
	{
		root = q.front() ;
		q.pop() ;
		cout << root->getData() ;
		if(root->getLeftChild())
		{
			q.push(root->getLeftChild()) ;
		}
		if(root->getRightChlid())
		{
			q.push(root->getRightChlid()) ;
		}
	}
}

//template<class T>
//void BinaryTree<T>::PreOrderTraverse(BinaryTreeNode<T> *root) const
//{
//	if(root != NULL)
//	{
//		cout << root->getData() ;
//		PreOrderTraverse(root->getLeftChild()) ;
//		PreOrderTraverse(root->getRightChlid()) ;
//	}
//}
template<class T>
void BinaryTree<T>::PreOrderTraverse(BinaryTreeNode<T> *root) const
{
	stack<BinaryTreeNode<T> *> s ;
	BinaryTreeNode<T> *p = root ;
	while(p != NULL || !s.empty())
	{
		while(p)
		{
			s.push(p) ;
			cout << p->getData() ;
			p = p->getLeftChild() ;
		}
		p = s.top() ;
		s.pop() ;
		p = p->getRightChlid() ;
	}
}

//template<class T>
//void BinaryTree<T>::InOrderTraverse(BinaryTreeNode<T> *root) const
//{
//	if(root != NULL)
//	{
//		InOrderTraverse(root->getLeftChild()) ;
//		cout << root->getData() ;
//		InOrderTraverse(root->getRightChlid()) ;
//	}
//
//}

template<class T>
void BinaryTree<T>::InOrderTraverse(BinaryTreeNode<T> *root) const 
{
	stack<BinaryTreeNode<T> *>s ;
	BinaryTreeNode<T> *p = root ;
	while(p != NULL || !s.empty())
	{
		while(p)
		{
			s.push(p) ;
			p = p->getLeftChild() ;
		}
		p = s.top() ;
		s.pop() ;
		cout << p->getData() ;
		p = p->getRightChlid() ;
	}
}

//template<class T>
//void BinaryTree<T>::PostOrderTraverse(BinaryTreeNode<T> *root) const
//{
//	if(root != NULL)
//	{
//		PostOrderTraverse(root->getLeftChild()) ;
//		PostOrderTraverse(root->getRightChlid()) ;
//
//		cout << root->getData() ;
//	}
//}
template<class T>
void BinaryTree<T>::PostOrderTraverse(BinaryTreeNode<T> *root) const
{
	typedef struct
	{
		BinaryTreeNode<T> *p ;
		unsigned tag ;
	}bintreenode ;

	stack<bintreenode>s ;
	bintreenode temp ;
	temp.p = root ;
	temp.tag = 0 ;
	while(temp.p != NULL || !s.empty())
	{
		while(temp.p)
		{
			
			s.push(temp) ;
			temp.p = temp.p->getLeftChild() ;
			temp.tag = 0 ;
		}
		temp = s.top() ;
	//	s.pop() ;
		if(temp.p->getRightChlid() == NULL || temp.tag == 1)
		{
			cout << temp.p->getData() ;
			if(temp.tag == 1)
			{
				temp.p = NULL ;
			}
			else
			{
				temp.p = temp.p->getRightChlid() ;
			}
			s.pop() ;
		//	temp = s.top() ;
		}
		else
		{
			s.pop() ;
			temp.tag = 1 ;                          //直接修改是无效的，应该弹出重新压栈
			s.push(temp) ;
			temp.p = temp.p->getRightChlid() ;
			while(temp.p)
			{
				temp.tag = 0 ;
				s.push(temp) ;
				temp.p = temp.p->getLeftChild() ;
				temp.tag = 0 ;
			}
		}
	}
}

//template<class T>
//void BinaryTree<T>::createBinTreePre(string pre, string mid) const 
//{
//	string iterator it = pre.begin();
//	string iterator temp = mid.find(*it) ;
//	BinaryTree<T> owntree(*it) ;
//	BinaryTreeNode<T> *cur = owntree.getroot() ;
//	if(strlen(pre) != strlen(mid))
//	{
//		cerr << "string wrong" << endl ;
//		return false ;
//	}
//	
//	owntree.InsertLeftChild(cur, 
//
//	
//
//	
//}

template<class T>
void BinaryTree<T>::createBinTreePre(BinaryTreeNode<T> * &tree, string pre, string in)
{
	int i ;
	unsigned pos ;
	string::iterator it ;
	if(strlen(pre.c_str()) != strlen(in.c_str()) || strlen(pre.c_str()) == 0)  //judge so that iterator can have a value
		                                                                       //otherwise runtime error
	{
		tree = NULL ;
		return ;
	}
	it = pre.begin() ;
	tree = new BinaryTreeNode<T> ;
	tree->SetData(*it) ;
	pos = in.find(*it) ;
	createBinTreePre(tree->m_leftChild, pre.substr(1, pos), in.substr(0,pos)) ;
	createBinTreePre(tree->m_rightChild, pre.substr(pos+1), in.substr(pos+1)) ;
}

template<class T>
void BinaryTree<T>::createBinTreePost(BinaryTreeNode<T>* &tree, string post ,string in)
{
	int i ;
	unsigned pos ;
	unsigned temppos ;
	string::iterator it ;
	if(strlen(post.c_str()) != strlen(in.c_str()) || strlen(post.c_str()) == 0)  //judge so that iterator can have a value
		                                                                       //otherwise runtime error
	{
		tree = NULL ;
		return ;
	}
	it = post.end() ;
	it-- ;
	//cout << *it << endl ;
	tree = new BinaryTreeNode<T> ;
	tree->SetData(*it) ;
	pos = in.find(*it) ;
	temppos = post.find(*it) ;
	createBinTreePost(tree->m_leftChild, post.substr(0,pos), in.substr(0,pos)) ;
	createBinTreePost(tree->m_rightChild, post.substr(pos,temppos-pos), in.substr(pos+1)) ;
}
#endif 