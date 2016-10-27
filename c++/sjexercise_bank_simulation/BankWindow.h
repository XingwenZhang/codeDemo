#include<iostream>
#include<queue>
#include"User.h"
using namespace std ;

class BankWindow
{
private:
	bool isBusy ;
	int id ;
	User client ;
	char type ;
public:
	bool HandleUser() ;
};