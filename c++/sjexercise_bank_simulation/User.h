#include<iostream>
#include<queue>
using namespace std ;

class User
{
public:
	int id ;
	bool isWait ;
	int ArriveTime ;
	int ServeTime ;
	char type ;

	User() ;
	void getServed() ;
};

User::User()
{
	id = -1 ;             //begin from 0
	isWait = 1 ;          //1 for wait
	ArriveTime = 0 ;      //every 2 second arrive one user
	ServeTime = 0 ;       //every 4 second handle one user
	type = '0' ;
}
void User::getServed()
{
	isWait = 0 ;
	ServeTime+=4 ;
}