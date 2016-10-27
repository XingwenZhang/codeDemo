#ifndef HUFFMANTREENODE_H
#define HUFFMANTREENODE_H
#include<iostream>
#include<map>
#include<string>
#include<fstream>
#include"huffmantreeNode.h"
#include"minheap.h"

using namespace std ;

template<class T>
struct EncodeNode
{
	T data ;
	string code ;
};

template<class T>
class HuffmanTree
{
public:
	
	HuffmanTreeNode<T>* parent;
	int leaf_num ;
	HuffmanTreeNode<T>* root ;   
	EncodeNode<T>* code_temp  ;
	void MergeTree(HuffmanTreeNode<T> *ht1, HuffmanTreeNode<T> *ht2, HuffmanTreeNode<T>* parent) ;
	
	HuffmanTreeNode<T>* Getroot()
	{
		
		return this->root ;
	}
	//EncodeNode<T>* encode ;
	HuffmanTree(double* weight, T* data, int n) ;
	void Encode(HuffmanTreeNode<T>* pTree,string str) ;
	void Decode();
};

template<class T>
HuffmanTree<T>::HuffmanTree(double* weight,T* data, int n)
{
	leaf_num = n ;
	code_temp = new EncodeNode<T>[leaf_num] ;
	MinHeap<HuffmanTreeNode<T> > heap(n) ;  
	HuffmanTreeNode<T>* NodeList = new HuffmanTreeNode<T>[n] ;
	for(int i = 0; i < n; i++)
	{
		NodeList[i].element = weight[i] ;
		NodeList[i].data = data[i] ;
		heap.Insert(NodeList[i]) ;
	}
	for(int i = 0; i < n-1; i++)
	{
		HuffmanTreeNode<T>* parent = new HuffmanTreeNode<T> ;
		HuffmanTreeNode<T>* firstchild = new HuffmanTreeNode<T> ;
		HuffmanTreeNode<T>* secondchild = new HuffmanTreeNode<T> ;
		*firstchild = heap.RemoveMin() ;
		*secondchild = heap.RemoveMin() ;
		MergeTree(firstchild, secondchild, parent) ;
		heap.Insert(*parent) ;
		root = parent ;
	}
	delete[] NodeList ;
}
template<class T>
void HuffmanTree<T>::MergeTree(HuffmanTreeNode<T> *ht1, HuffmanTreeNode<T> *ht2, HuffmanTreeNode<T>* tparent)
{
	ht1->parent = tparent ;
	ht2->parent = tparent ;
	tparent->element = ht1->element +  ht2->element ;
	tparent->lchild = ht1 ;
	tparent->rchild = ht2 ;
	
}
template<class T>
void HuffmanTree<T>::Encode(HuffmanTreeNode<T>* pTree,string str)
{
	static int i = 0 ;
	if(pTree==NULL)
		return;
	ofstream out;
	if(pTree->lchild==NULL)   //是叶结点，递归结束
	{
		out.open("output.txt",ios_base::app);
		if(!out)
		{
			cout<<"error!out"<<endl;
			exit(0);
		}
        out<<pTree->data<<str<<endl;
		

		code_temp[i].data = pTree->data ;
		code_temp[i].code = str ;
		i++ ;
		

		cout<<"\n"<<pTree->data<<"     "<<str;
		out.close();
		return;
	}
	                     //非叶结点
	string temp=str;
	str+="0";
	Encode(pTree->lchild,str);
	temp+="1";
	Encode(pTree->rchild,temp);
}
template<class T>
void HuffmanTree<T>::Decode()
{
	ifstream infile;
	infile.open("outcode.txt");
	if(!infile)
	{
		cout<<"cannot open outputs.txt "<<endl;
		return ;
	}
	
	HuffmanTreeNode<T>* pointer = root;
	while(infile.good())
	{
		char a = infile.get() ;
		if(a=='1')
			pointer = pointer->rchild;
		else if(a=='0')
			pointer = pointer->lchild;
		else
			return ;
		if(pointer->lchild==NULL)
		{
			ofstream outfile("translate.txt",ios_base::app) ;
			outfile<<pointer->data;
			pointer = root;
			outfile.close();
		}
	}
	cout<<endl;
	infile.close() ;
}

//template<class T>
//void HuffmanTree<T>::DeleteTree(HuffmanTreeNode<T>* root)
//{
//	if(root != NULL)
//	{
//		DeleteTree(root->lchild) ;
//		DeleteTree(root->rchild) ;
//		delete root ;
//	}
//}

//template<class T>
//void HuffmanTree<T>::Encode(HuffmanTreeNode<T>* proot) 
//{
//	static EncodeNode<T>* code_temp = new EncodeNode<T>[leaf_num] ;   //leaf num encodes 
//	//static HuffmanTreeNode<T>* p = proot ;
//	static int i = 0; 
//	//static int j = 0 ;
//	while(proot != NULL)
//	{
//		if(root != proot)
//		{
//			if(proot->parent->lchild == proot)
//			{
//				code_temp[i].code += '0' ;
//			}
//			else
//			{
//				code_temp[i].code += '1' ;
//			}
//		}
//	//	if(proot != NULL)
//		if(proot->lchild == NULL)    //if is leaf
//		{
//			code_temp[i++].data = proot->data ;
//		}
//		
//		Encode(proot->lchild) ;
//		Encode(proot->rchild) ;
//	}
//	encode = code_temp ;
//}

//template<class T>
//void HuffmanTree<T>::Decode(EncodeNode<T>* decode)
//{
//
//}

//template<class T>
//void Encode(HuffmanTreeNode<T>* proot) 
//{
//	static EncodeNode<T> * testencode ;
//	static EncodeNode<T>* code_temp = new EncodeNode<T>[40] ;   //leaf num encodes 
//	//static HuffmanTreeNode<T>* p = proot ;
//	static int i = 0; 
//	static int j = 1 ;
//	while(proot != NULL)
//	{
//		if( j-- != 1 )
//		{
//			if(proot->parent->lchild == proot)
//			{
//				code_temp[i].code += '0' ;
//			}
//			else
//			{
//				code_temp[i].code += '1' ;
//			}
//		}
//	//	if(proot != NULL)
//		if(proot->lchild == NULL)    //if is leaf
//		{
//			code_temp[i++].data = proot->data ;
//		}
//		
//		Encode(proot->lchild) ;
//		Encode(proot->rchild) ;
//	}
//	testencode = code_temp ;
//}

//template<class T>
//EncodeNode<char>* Encode(HuffmanTreeNode<char>* proot,string str) 
//{
//	//static EncodeNode<char> * testencode ;
//	static EncodeNode<char>* code_temp = new EncodeNode<char>[7] ;  
//	static int i = 0; 
//	static int j = 1 ;
//	if(proot != NULL)
//	{
//		if( j-- != 1 )
//		{
//			if(proot->parent->lchild == proot)
//			{
//				code_temp[i].code += '0' ;
//			}
//			else
//			{
//				code_temp[i].code += '1' ;
//			}
//		}
//		if(proot->lchild == NULL)    //if is leaf
//		{
//			code_temp[i++].data = proot->data ;
//		}
//		
//		Encode(proot->lchild) ;
//		Encode(proot->rchild) ;
//	}
//	return code_temp ;
//}



#endif