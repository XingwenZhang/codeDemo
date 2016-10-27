#include"BinaryTree.h"
#include"BinaryTreeNode.h"
#include<iostream>
using namespace std ;

int main(int argc, char **argv)
{
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
	cout << "input the pre" << endl ;

	string pre ;
	cin >> pre ;

	cout << "input the in " << endl ;

	string in ;
	cin >> in ;

	BinaryTree<char> testTree ;
	testTree.createBinTreePre(testTree.getRoot(), pre, in) ;
	testTree.PostOrderTraverse(testTree.getRoot()) ;	

	cout << endl ;
	cout << "input the post" << endl ;

	string post ;
	cin >> post ;

	cout << "input the in " << endl ;

	string IN ;
	cin >> IN ;

	BinaryTree<char> testtreepost ;
	testtreepost.createBinTreePost(testTree.getRoot(), post, IN) ;
	testtreepost.PreOrderTraverse(testTree.getRoot()) ;

	return 0 ;
}