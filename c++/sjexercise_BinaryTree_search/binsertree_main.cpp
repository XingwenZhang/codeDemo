#include"BinSerTree.h"
#include<iostream>
using namespace std ;

int main(int argc, char* argv[])
{
	BinSerTree<int> serTree ;
	serTree.insert(1) ;
	serTree.insert(2) ;
	serTree.insert(3) ;
	serTree.insert(4) ;
	serTree.inorder(serTree.root) ;
	BinSerTreeNode<int>* tmp = serTree.search(serTree.root,3) ;
	serTree.remove(tmp) ;
	serTree.inorder(serTree.root) ;
	return 0 ;
}