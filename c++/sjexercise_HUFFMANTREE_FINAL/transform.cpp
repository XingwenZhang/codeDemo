


#include<fstream>
#include<iostream>
#include<string>
void transform ()
{

	ifstream infile("data.txt") ;
	if(infile.good())
	{
		string c ;
		for(int i = 0; i < 8; i++)
			c += infile.get() ;


	}
}
