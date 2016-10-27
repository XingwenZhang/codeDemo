#include"BinaryTreeNode.h"
#include"BinaryTree.h"
#include<iostream>
using namespace std ;

int main(int argc, char **agrv)
{
	//BinaryTree<char> myBinTree('a') ;
	//myBinTree.InsertLeftChild(myBinTree.getRoot() , 'D') ;
	//myBinTree.InsertRightChild(myBinTree.getRoot(), 'G') ;
	//myBinTree.InsertLeftChild(myBinTree.getRoot(), 'B') ;
	//myBinTree.InsertRightChild(myBinTree.getRoot()->getLeftChild(), 'E') ;
	//myBinTree.InsertRightChild(myBinTree.getRoot(), 'C') ;
	//myBinTree.InsertLeftChild(myBinTree.getRoot()->getRightChlid(), 'F') ;

	//cout << "is this BinaryTree empty? " << myBinTree.IsEmpty() << endl;
	//cout << "the data in the root is " << myBinTree.Retrieve(myBinTree.getRoot()) << endl ;
	//cout << "give a new datium 'A' to root" ;

	//myBinTree.Assign(myBinTree.getRoot() , 'A') ;

	//cout << "now the data in the root is " << myBinTree.Retrieve(myBinTree.getRoot()) << endl ;
	BinaryTree<char>myBinTree('A') ;
	myBinTree.InsertLeftChild(myBinTree.getRoot(),'D');
	myBinTree.InsertLeftChild(myBinTree.getRoot(),'C');
	myBinTree.InsertLeftChild(myBinTree.getRoot(),'B');

	myBinTree.InsertRightChild(myBinTree.getRoot(),'M');

	cout << "traverse by level :" << endl ;

	myBinTree.LevelOrderTraverse(myBinTree.getRoot()) ; 

	cout << endl << "the preordertraverse is" << endl ;

	myBinTree.PreOrderTraverse(myBinTree.getRoot()) ;

	cout << endl << "the inordertraverse is" << endl ;

	myBinTree.InOrderTraverse(myBinTree.getRoot())  ;

	cout << endl << "the postordertraverse is" << endl ;

	myBinTree.PostOrderTraverse(myBinTree.getRoot()) ;

	cout << endl ;

	return 0 ;

}