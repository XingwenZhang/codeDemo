#include<fstream>
#include<iostream>
#include<map>
using namespace std ;

int main(int argc, char** argv)
{
	//ifstream infile("Article.txt") ;
	///*while(infile.good())
	//{
	//	char c = infile.get() ;
	//	if(infile.good())
	//		cout << c ;
	//}
	//infile.close() ;*/
	//int i = 0;
	//map<char,int> char_count ;
	//while(infile.good())
	//{
	//	char c = infile.get() ;
	//	if(infile.good())
	//	{
	//		++char_count[c] ;
	//		i++;
	//	}
	//}
	////map<char,int>::iterator it = char_count.find('a') ;
	//
	////cout << it->second ;
	///*cout << char_count['a'];
	//cout << endl ;
	//cout << char_count.size() << endl ;*/
	//cout << i ;
	//infile.close() ;
	//return 0 ;
	int sum = 0 ;
	double s = 0.0 ;
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
	int n = char_count.size() ;
	double* rate = new double[n] ;
	map<char,int>::iterator it = char_count.begin() ;
	for(int i = 0;it != char_count.end(); i++,it++)
	{
		rate[i] = double(it->second)/ sum ;
		cout << rate[i] << endl ;
	}
	for(int i = 0; i < 40 ; i++)
	{
		s += rate[i] ;
	}
	cout << "------------------"<< endl ;
	cout << s ;
	infile.close() ;
	//HuffmanTree<char> tree_test()
	return 0 ;
}