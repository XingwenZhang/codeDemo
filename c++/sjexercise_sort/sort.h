#ifndef SORT_H
#define SORT_H

#include<iostream>
using namespace std ;

template<class T>
void InsertSort(T data[], int n)
{
	int i , j ;
	for(i = 1; i < n; i++)
	{
		T temp = data[i] ;
		j = i - 1;
		while(j >= 0 && data[j] > temp)
		{
			data[j+1] = data[j] ;
			j-- ;
		}
		data[j+1] = temp ;
	}
}


template<class T>
void BinaryInsertSort(T data[], int n)
{
	int left, mid, right, p ;
	for(p = 1; p < n; p++)
	{
		T temp = data[p] ;
		left = 0;
		right = p - 1;
		while(left <= right)
		{
			mid = (left + right)/2 ;
			if(data[mid] > temp)
				right = mid - 1;
			else
				left = mid + 1;
		}
		for(int i = p-1; i >= left; i--)
			data[i+1] = data[i] ;
		data[left] = temp ;
	}
}

template<class T>
void ShellSort(T data[], int n)
{
	int d = n/2 ;
	while(d >= 1)
	{
		for(int k = 0; k < d; k++)
		{
			for(int i = k+d; i < n; i+=d)
			{
				T temp = data[i] ;
				int j = i - d ;
				while(j >= k && data[j] > temp)
				{
					data[j+d] = data[j] ;
					j -= d ;

				}
				data[j+d] = temp ;
			}
		}
		d = d/2 ;
	}
}

template<class T>
void BubbleSort(T data[], int n)
{
	int flag = 0 ;
	for(int i = 0; i < n; i++)
	{
		flag = 0;
		for(int j = 1; j < n-1; j++)//应该是n不是n-1
		{
			if(data[j] < data[j-1])
			{
				flag = 1;
				T t = data[j] ;
				data[j] = data[j-1] ;
				data[j-1] = t ;
			}
		}
		if(flag == 0)
			return ;
	}
}

template<class T>
int Partition(T data[],int left, int right)
{
	T pivot = data[left] ;
	while(left < right)
	{
		while(left < right && data[right] > pivot)
			right -- ;

		data[left] = data[right] ;
		while(left < right && data[left] <= pivot)
			left ++ ;

		data[right] = data[left] ;
	}
	data[left] = pivot ;
	return left ;
}
template<class T>
void QuickSort(T data[], int left, int right)
{
	if(left < right)
	{
		int p = Partition(data, left ,right) ;
		QuickSort(data, left, p - 1) ;
		QuickSort(data, p+1, right) ;
	}
}

template<class T>
void SelectSort(T data[], int n)
{
	for(int i = 1; i < n; i ++)
	{
		int k = i - 1; 
		for(int j = i; j < n; j++)
		{
			if(data[j] < data[k])
				k = j ;
		}
		if(k != i -1)
		{
			T t = data[k] ;
			data[k] = data[i-1] ;
			data[i -1] = t ;
		}
	}
}
#endif