#ifndef UFSETS_H
#define UFSETS_H

class UFSets
{
public:
	int n ;
	int* root ;
	int* next ;
	int* length ;
	UFSets(int size)
	{
		n = size ;
		root = new int[n] ;
		next = new int[n] ;
		length = new int[n] ;
		for(int i = 0; i < n; i++)
		{
			root[i] = next[i] = i ;
			length[i] = 1 ;
		}
	}
	int Find(int v){return root[v] ;}
	void Union(int v, int u) ;
};
void UFSets::Union(int v, int u)
{
	if(root[u] == root[v])
		return ;
	else if(length[root[v]] < length[root[u]])
	{
		int rt = root[v] ;
		length[root[u]]+=length[rt] ;

		root[rt]= root[u] ;
		for(int j = next[rt]; j!=rt ; j= next[j])
			root[j] = root[u] ;
		int temp ;
		temp = next[rt] ;
		next[rt] = next[root[u]] ;
		next[root[u]] = temp ;
	}
	else
	{
		int rt = root[u] ;
		length[root[v]] += length[rt] ;

		root[rt] = root[v] ;
		for(int j = next[rt] ; j!=rt ; j=next[j])
			root[j] = root[v] ;

		int temp ;
		temp = next[rt] ;
		next[rt] = next[root[v]] ;
		next[root[v]] = temp ;

	}
}


#endif