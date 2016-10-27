#include"OfficialUser.h"
#include"VIPUser.h"
#include"NormalUser.h"
#include"OfficialBankWindow.h"
#include"VIPBankWindow.h"
#include"NormalBankWindow.h"
#include<queue>
#include<list>
class Simulater
{
public:
	queue<NormalUser> NormalUserQueue ;
	queue<VIPUser> VIPUserQueue ;
	queue<OfficialUser> OfficialUserQueue ;
	list<NormalBankWindow> NormalBankWindowList ;
	list<VIPBankWindow> VIPBankWindowList ;
	list<OfficialBankWindow> OfficialBankWindowList ;
	static int i ;
	void CustomerEnter(User* temp) ;
	void CallCustomer() ;
	char CreateNumber() ;
	Simulater() ;
};

Simulater::Simulater()
{
	NormalBankWindow NormalBankWindow1,NormalBankWindow2, NormalBankWindow3 ;
	OfficialBankWindow OfficialBankWindow1 ;
	VIPBankWindow VIPBankWindow1 ;
	NormalBankWindowList.push_back(NormalBankWindow1) ;
	NormalBankWindowList.push_back(NormalBankWindow2) ;
	NormalBankWindowList.push_back(NormalBankWindow3) ;
	OfficialBankWindowList.push_back(OfficialBankWindow1);
	VIPBankWindowList.push_back(VIPBankWindow1) ;
}

void Simulater::CustomerEnter(User* temp)
{
	switch(temp->type-'0')                       //type is char not int
	{
	case 1:
		NormalUserQueue.push(dynamic_cast<NormalUser*>(temp)) ;
		break ;
	case 2:
		OfficialUserQueue.push(dynamic_cast<OfficialUser*>(temp)) ;
		break ;
	case 3:
		VIPUserQueue.push(dynamic_cast<VIPUser*>(temp)) ;
		break ;
	default:
		cout<< "wrong" << endl;
		exit(1);
		break ;
	}
}
void  Simulater::CallCustomer()
{
	cout << "";
}

char Simulater::CreateNumber()
{
	cout << "choose the kind of service" << endl ;
	cout << "1 for NormalUser" << endl ;
	cout << "2 for OfficialUser" << endl ;
	cout << "3 for VIPUser" << endl ;
	char service_kind ;
	cin >> service_kind ;
	return service_kind ;
}