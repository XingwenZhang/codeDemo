#include<iostream>

using namespace std ;

//int binarysearch(int* p,int n, int key)
//{
//	int m=0 ;
//	
//	while(key != p[(n+m)/2] && n != 0) 
//	{
//		if(key < p[n/2]) 
//			n = n /2 ;
//		else
//			m = n/2 ;
//			n = (m + n)/2 ;
//	}
//	if(n == 0)
//		if(key == p[0])
//			return 0 ;
//		else
//			return -1 ;
//		
//	else
//		return (m+n)/2 ;
//
//}
int binarysearch(int* p, int n, int key)
{

	int low, high, mid;
            low = 0;
            high = n - 1;
            while (low <= high)
            {
                mid = (low + high) / 2;
                if (p[mid] < key)
                {
                    low = mid + 1;
                }
                else if (p[mid]>key)
                {
                    high = mid - 1;
                }
                else 
                {
                    return mid;
                }
          }
         return -1;
}
int main(int argc, char** argv)
{
	int temp[10] = {0,1,2,3,4,5,6,7,8,9} ;
	int t ;
	t = binarysearch(temp,10,8) ;
	cout << t << endl ;
	return 0 ;
}