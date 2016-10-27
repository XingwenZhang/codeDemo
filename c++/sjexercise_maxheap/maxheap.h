
#ifndef MAXHEAP_H
#define MAXHEAP_H
template<class T>
class MaxHeap
{
private:
	T* heapArray ;
	int CurrentSize ;
	int MaxSize ;
public:
	MaxHeap(T* array, int num, int max) ;
	 ~MaxHeap() ;
	void BuildHeap() ;
	//bool isLeaf(int pos) const ;
//	int leftchild(int pos) const ;
	//int rightchild(int pos) const ;
	//int parent(int pos) const ;
	bool Remove(int ele) ;
	void SiftDown(int left) ;
	void SiftUp(int position) ;
	bool Insert(const T& NewNode) ;
	//void MoveMax() ;
	void RemoveMax() ;
	void show() ;
};
template<class T>
MaxHeap<T>::MaxHeap(T* array, int num, int max)
{
	this->heapArray = array ;
	this->CurrentSize = num ;
	this->MaxSize = max ;
}
template<class T>
MaxHeap<T>::~MaxHeap()
{
	;
}

template<class T>
void MaxHeap<T>::BuildHeap()
{
	for(int i = CurrentSize/2 - 1; i>=0; i--)
		SiftDown(i) ;
}
template<class T>
void MaxHeap<T>::SiftDown(int left)
{
	int i = left ;
	int j = 2 * i + 1 ;
	T temp = heapArray[i] ;

	while(j < CurrentSize)
	{
		if((j < CurrentSize - 1) && (heapArray[j] < heapArray[j+1]))
			j ++ ;

		if(temp < heapArray[j])
		{
			heapArray[i] = heapArray[j] ;
			i = j ;
			j = 2*j + 1 ;
		}
		else 
			break ;
	}
	heapArray[i] = temp ;
}
template<class T>
void MaxHeap<T>::SiftUp(int position)
{
	int i=position,j=(i-1)/2;
	T temp;
	while(j>0)
	{
		if(heapArray[i]<heapArray[j]){break;}
		else
		{
		    temp=heapArray[j];
			heapArray[j]=heapArray[i];
			heapArray[i]=temp;
		}
		i=j;
		j=(j-1)/2;
	}
	if(heapArray[0]<heapArray[1])
	{
		temp=heapArray[0];
		heapArray[0]=heapArray[1];
		heapArray[1]=temp;
	}
}
template<class T>
bool MaxHeap<T>::Insert(const T& ele)
{
	if(CurrentSize+1>=MaxSize)
	{
		cout<<"overflow "<<endl;
		return false ;
	}
	heapArray[CurrentSize]=ele;
	SiftUp(CurrentSize);
	CurrentSize++;
	return true ;
}
template<class T>

void MaxHeap<T>::show()
{
	int i;
	for(i=0;i<CurrentSize;i++)
	{
		cout<<heapArray[i]<<' ';
	}
	cout<<endl;
}
template<class T>
bool MaxHeap<T>:: Remove(int ele)
{
	int i,temp;
	for(i=0;i<CurrentSize;i++)
	{
		if(heapArray[i]==ele){break;}
	}
	if(i==CurrentSize)
	{
		 cout<<"no find "<<endl ;
		 return false;
 	}
	temp=heapArray[i];
	heapArray[i]=heapArray[CurrentSize-1];
	heapArray[CurrentSize-1]=0;CurrentSize--;
	for(i=0;i<CurrentSize/2-1;i++)
		SiftDown(i);
	return true;
}
template<class T>
void MaxHeap<T>::RemoveMax()
{
	T temp;
	int i;
	temp=heapArray[0];
	heapArray[0]=heapArray[CurrentSize-1];
	heapArray[CurrentSize-1]=temp;
	heapArray[CurrentSize-1]=0;
	CurrentSize--;
	for(i=0;i<CurrentSize;i++)
		SiftDown(i);
}


#endif MAXHEAP_H