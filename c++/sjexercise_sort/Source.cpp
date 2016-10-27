#include"sort.h"
#include<time.h>

int main(int argc, char* argv[])
{
	int* test = new int[100] ;
	srand(time(0)) ;
	for(int i = 0; i < 100; i++)
	{
		test[i] = int(rand() % 10000) ;
	}
	//InsertSort(test,100) ;
	//BinaryInsertSort(test,100) ;
	//ShellSort(test,100);
	//BubbleSort(test,100);
	//QuickSort(test,0,99);
	//SelectSort(test,100);
	for(int i = 0; i < 100; i++)
	{
		cout << test[i] << "	";
	}
	cout << endl ;
	return 0 ;
}