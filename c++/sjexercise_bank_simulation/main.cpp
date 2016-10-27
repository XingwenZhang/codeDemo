#include"Simulater.h"
#include<iostream>
using namespace std ;

int main(int argc ,char* argv[])
{
	int i = 0 , j = 0 , k = 0 ;
	int intemp ;
	char chtemp ;
	Simulater TEST_SIMULATER ;
	cout << "Welcome to the CHINA BANK" << endl ;
	while(true)
	{
		chtemp = TEST_SIMULATER.CreateNumber() ;
		intemp = chtemp - '0' ;
		switch(intemp)
		{
		case 1 :
			cout << "dear customer your service_number is:" << 1000+i << endl ;
			TEST_SIMULATER.CustomerEnter()
			i++ ;
			break ;
		case 2:
			cout << "dear customer your service_number is:" << 2000+j << endl ;
			j++ ;
			break ;
		case 3:
			cout << "dear customer your service_number is:" << 3000+k << endl ;
			k++ ;
			break ;
		}
		
			

	}
	

}