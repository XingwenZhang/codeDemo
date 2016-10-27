#include"huffmantree.h"
#include"huffmantreeNode.h"
#include<iostream>
#include<map>
#include<string>
#include<fstream>
using namespace std ;

void display(HuffmanTreeNode<char>* root)
{
	if(root!=NULL)
	{
		cout << root->element << endl ;
		display(root->lchild) ;
		display(root->rchild) ;
	}
	
}

int main(int argc, char** argv)
{
	//int n = 7 ;
	//double rate[7] = {0.4,0.3,0.15,0.05,0.04,0.03,0.03} ;
	////char data_store[7] = {'A','B','C","D","E","F","G"} ;
	//char data_store[7] = {'A','B','C','D','E','F','G'} ;
	int sum = 0 ;
	map<char,int> char_count ;
	ifstream infile("Article.txt") ;
	while(infile.good())
	{
		char c = infile.get() ;
		if(infile.good())
		{
			++char_count[c] ;
			sum++ ;
		}
	}
	//cout << "zonghe is "<<endl ;
	//cout << sum << endl ;
	infile.close() ;
	int n = char_count.size() ;
	double* rate = new double[n] ;
	map<char,int>::iterator it = char_count.begin() ;
	for(int i = 0;it != char_count.end(); i++,it++)
	{
		rate[i] = static_cast<double>(it->second) / sum ;
		//cout << rate[i] << endl ;
	}
	it = char_count.begin() ;
	char* data_store = new char[n] ;
	for(int i = 0;it!=char_count.end();i++, it++)
	{
		data_store[i] = it->first ;
		//cout << data_store[i] << '	';
	}
	HuffmanTree<char> tree_test(rate, data_store, n) ;
	HuffmanTreeNode<char>* proot = tree_test.root ;
//	cout << proot->lchild->element ;
	EncodeNode<char>* temp = NULL;
	string str;
    tree_test.Encode(proot,str) ;
	ifstream iinfile("Article.txt") ;
	ofstream ofile ;
	ofile.open("outcode.txt") ;
	while(iinfile.good())
	{
		char c = iinfile.get() ;
		for(int i=0; i< tree_test.leaf_num; i++)
		{
			if(c == tree_test.code_temp[i].data)
			{
				ofile << tree_test.code_temp[i].code ;
			}
		}
	}
	iinfile.close();
	ofile.close() ;
	tree_test.Decode() ;
	return 0 ;
}
