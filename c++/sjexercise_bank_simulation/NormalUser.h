
#include"User.h"
#include<iostream>
using namespace std ;

class NormalUser : public User
{
public:
	NormalUser() ;
	void getServed() ;
};

NormalUser::NormalUser()
{
	id = -1 ;             //begin from 0
	isWait = 1 ;          //1 for wait
	ArriveTime = 0 ;      //every 2 second arrive one user
	ServeTime = 0 ;       //every 4 second handle one user
	type = '0' ;
}
void NormalUser::getServed()
{
	ServeTime+=4 ;
	isWait = 0 ;
}
