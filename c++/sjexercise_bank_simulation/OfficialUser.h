

#include"User.h"
#include<iostream>
using namespace std ;

class OfficialUser:public User
{
public:
	OfficialUser() ;
	void getServed() ;
};