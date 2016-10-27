#include<iostream>
#include<string>
#include<assert.h>
using namespace std ;
int *mynext(string p) ;
int KMP(string T, string P, int *N, int startIndex)
{
	//using namespace std ;
	int lastIndex = T.size() - P.size() ;
	if((lastIndex - startIndex) > 0)
		return -1 ;
	int i ;
	int j = 0 ;
	for(i = startIndex; i < T.size(); i++)
	{
		while(P[j] != T[i] && j > 0 )
			j = N[j - i] ;
		if(P[j] == T[i])
			j++ ;
		if(j == P.size())
			return (i - j + 1) ;
	}
	return -1 ;
}

int main(int argc, char* argv[])
{
	//using namespace std ;
	string t = "abcaabbcabcaabdab" ;
	int* temp = NULL ;
	temp = mynext(t) ;
	for(int i = 0 ; i < t.size() ; i ++)
	{
		cout << temp[i] << endl ;
	}
	return 0 ;
}

