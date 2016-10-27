
#ifndef ADJGRAPH_H
#define ADJGRAPH_H

#include"Graph.h"

template<class EdgeType>
class AdjGraph : public Graph<EdgeType>
{
public:
	int **matrix ;                    //ָ���ڽӾ����ָ��

	AdjGraph(int verticesNum):Graph<EdgeType>(verticesNum)
	{
		int i, j ;
		martrix = (int**) new int*[vertexNum] ;
		for(i = 0; i < vertexNum; i++)
		{
			matrix[i] = new int[vertexNum] ;
		}
		for(i = 0; i < vertexNum; i++)                    //�����ʼ��Ϊ0
			for(j = 0; j < vertexNum; j++)
				matrix[i][j] = 0;
	}
	AdjGraph(int verticesNum, int** temp):Graph<EdgeType>(verticesNum)
	{
		int i, j ;
		matrix = (int**) new int*[vertexNum] ;
		for(i = 0; i < vertexNum; i++)
		{
			matrix[i] = new int[vertexNum] ;
		}
		for(i = 0; i < vertexNum; i++)               //�����ʼ��Ϊ����ľ���
			for(j = 0; j < vertexNum; j++)
				matrix[i][j] = temp[i][j] ;
	}

	~AdjGraph()                                      //��ά������ͷ�
	{
		for(int i = 0; i < vertexNum; i++)
			delete [] matrix[i] ;

		delete [] matrix ;
	}

	Edge<EdgeType> FirstEdge(int oneVertex)
	{
		Edge<EdgeType> tmpEdge ;
		tmpEdge.start = oneVertex ;
		for(int i = 0; i < vertexNum ;i ++)
		{
			if(matrix[oneVertex][i] != 0)                //��Ϊ0˵���б�
			{
				tmpEdge.end = i ;
				tmpEdge.weight = matrix[oneVertex][i] ;  //������Ȩͼ
				break ;                                  //һ���ҵ���һ���߾��˳�ѭ��
			}
		}
		return tmpEdge ;
	}
	Edge<EdgeType> NextEdge(Edge<EdgeType> oneEdge)      //���������ı��ظ�����˲��ñ�����Ϊ����
	{
		Edge<EdgeType> tmpEdge ;
		tmpEdge.start = oneEdge.start ;
		for(int i = oneEdge.end+1; i < vertexNum; i++)   //����һ���߿�ʼ����
		{
			if(matrix[oneEdge.start][i] != 0)
			{
				tmpEdge.end = i ;                         //�ҵ���һ����ͬ�ı߾��˳�ѭ��
				tmpEdge.weight = matrix[oneEdge.start][i] ;
				break ;
			}
		}
		return tmpEdge ;
	}

	void setEdge(int start, int end, int weight)
	{
		if(matrix[start][end] == 0)
		{
			edgeNum ++ ;
		}
		matrix[start][end] = weight ;
	}
	void delEdge(int start, int end)
	{
		if(matrix[start][end] != 0)
			edgeNum-- ;
		matrix[start][end] = 0 ;             //��ʾû�б�
											 //�����������ͼ
	}
};

#endif