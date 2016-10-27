#ifndef MINHEAP_H
#define MINHEAP_H
#include<iostream>
#include<map>
#include<string>
#include<fstream>


template<class T>
class MinHeap
{
private:
	T* heapArray ;
	//int CurrentSize ;
	int MaxSize ;
	void BuildHeap() ;            //build a heap 
	void Swap(int a, int b) ;
public:
	int CurrentSize ;
	MinHeap(const int n,T Tarray[]) ;
	MinHeap(const int n) ;
	~MinHeap() ;
	bool isEmpty();				// 如果堆空，则返回真
    bool isLeaf(int pos) const;	    		// 如果是叶结点，返回TRUE
  	int leftchild(int pos) const;	   		// 返回左孩子位置
  	int rightchild(int pos) const;		// 返回右孩子位置
  	int parent(int pos) const;			// 返回父结点位置
	bool Insert(const T& newNode);		// 向堆中插入新元素newNode
	T& RemoveMin();			            // 从堆顶删除最小值
    bool Remove(int pos); 		// 删除给定下标的元素
	void SiftUp(int position);		 // 从position向上开始调整，使序列成为堆
	void SiftDown(int left);         	// 向下筛选，参数left表示开始处理的数组下标
	void show() ;
};
template<class T>
MinHeap<T>::MinHeap(const int n,T Tarray[])
{
	if(n <= 0)
	{
		cerr << "the parameter is invalid" << endl ;
		return ;
	}
	CurrentSize = n ;
	MaxSize = n ;
	heapArray = new T[MaxSize] ;
	int i = 0 ;
	while(i < n)
	{
		heapArray[i] = Tarray[i] ;
		i++ ;
	}
	BuildHeap() ;

}

template<class T>
MinHeap<T>::MinHeap(const int n)
{
	if(n <= 0)
	{
		cerr << "the parameter is invalid" << endl ;
		return ;
	}
	CurrentSize = 0 ;
	MaxSize = n ;
	heapArray = new T[MaxSize] ;
}
template<class T>
MinHeap<T>::~MinHeap()
{
	delete[] heapArray ;
}

template<class T>
bool MinHeap<T>::isEmpty() 

{
	if (CurrentSize == 0)
		return true ;
	else
		return false ;
}

template<class T>
bool MinHeap<T>::isLeaf(int pos) const
{
	if ((pos < CurrentSize) && (pos >= CurrentSize/2))
		return true ;
	else
		return false ;
}

//there is no judge if the child is large than the currentsize before return
//the position of child whatever the child exist or not is valid 
template<class T>
int MinHeap<T>::leftchild(int pos) const 
{
	return 2*pos + 1 ;
}

template<class T>
int MinHeap<T>::rightchild(int pos) const 
{
	return 2 * pos + 2 ;
}

template<class T>
int MinHeap<T>::parent(int pos) const 
{
	return ( pos - 1 ) / 2 ;
}

template<class T>
bool MinHeap<T>::Insert(const T& newNode)
{
	if(CurrentSize+1 > MaxSize)
	{
		cerr << " the heap is already full enough "<< endl ;
		return false ;
	}
	heapArray[CurrentSize] = newNode ;
	//after insert in order to keep the minheap so must do some changes from down to the top
	SiftUp(CurrentSize) ;
	CurrentSize++ ;
	return true ;
}

template<class T>
T& MinHeap<T>::RemoveMin()
{
	if(CurrentSize == 0)
	{
		cerr << " heap is already empty " << endl ;
		exit(1) ;
	}
	//--currentsize not only get the position of the last element but also delete the last element
	Swap(0, --CurrentSize) ;
	if(CurrentSize > 1)
		SiftDown(0) ;
	return heapArray[CurrentSize] ;
}

template<class T>
bool MinHeap<T>::Remove(int pos)
{
	if((pos > CurrentSize-1) || (CurrentSize == 0) || pos < 0 )
	{
		cerr << " no remove this position element " << endl ;
		return false ;
	}
	T node ;
	node = heapArray[pos] ;
	heapArray[pos] = heapArray[--CurrentSize] ;
	if(heapArray[parent(pos)] > heapArray[pos])
	{
		SiftUp(pos) ;
	}
	else
		SiftDown(pos) ;
	return true ;
}

template<class T>
void MinHeap<T>::SiftUp(int position) 
{
	T temp = heapArray[position] ;
	while ( (position > 0) && (heapArray[parent(position)] > heapArray[position]) )
	{
		T tt ;
		tt = heapArray[position] ;
		heapArray[position] = heapArray[parent(position)] ;//
		heapArray[parent(position)] = tt ;
		position = parent(position) ;//
	}

	//heapArray[position] = temp ;
}

template<class T>
void MinHeap<T>::SiftDown(int left)
{
	int i = left ;                //record the parent node
	int j = leftchild(i) ;        //record the min child node 
	T temp = heapArray[i] ;
	while(j < CurrentSize)
	{
		if ( (j < CurrentSize-1) && (heapArray[j] > heapArray[j+1]) )
		{
			j++ ;                 //ensure the j is the min value's index
		}
		/*if(heapArray[i] > heapArray[j])
		{
			heapArray[i] = heapArray[j] ;
			i = j ;
			j = leftchild(j) ; 
		}*/
		if(heapArray[i] > heapArray[j])
		{
			T tt ;
			tt = heapArray[i] ;
			heapArray[i] = heapArray[j] ;
			heapArray[j] = tt ;
			i = j ;
			j = leftchild(j) ;
		}
		else 
			break ;
	}
	//heapArray[i] = temp ;
}

template<class T>
void MinHeap<T>::BuildHeap()
{
	for(int i = CurrentSize/2-1; i >= 0; i--)             //筛选法
	{
		SiftDown(i) ;
	}
}

template<class T>
void MinHeap<T>::Swap(int a ,int b)
{
	T temp ;
	temp = heapArray[a] ;
	heapArray[a] = heapArray[b] ;
	heapArray[b] = temp ;
}

template<class T>
void MinHeap<T>::show()
{
	for(int i = 0; i < CurrentSize; i++)
	{
		cout << heapArray[i] << '	' ;
	}
	cout << endl ;
}

#endif
