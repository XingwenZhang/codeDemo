
#ifndef ADJGRAPH_H
#define ADJGRAPH_H

#include"Graph.h"

template<class EdgeType>
class AdjGraph : public Graph<EdgeType>
{
public:
	int **matrix ;                    //指向邻接矩阵的指针

	AdjGraph(int verticesNum):Graph<EdgeType>(verticesNum)
	{
		int i, j ;
		martrix = (int**) new int*[vertexNum] ;
		for(i = 0; i < vertexNum; i++)
		{
			matrix[i] = new int[vertexNum] ;
		}
		for(i = 0; i < vertexNum; i++)                    //矩阵初始化为0
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
		for(i = 0; i < vertexNum; i++)               //矩阵初始化为传入的矩阵
			for(j = 0; j < vertexNum; j++)
				matrix[i][j] = temp[i][j] ;
	}

	~AdjGraph()                                      //二维矩阵的释放
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
			if(matrix[oneVertex][i] != 0)                //不为0说明有边
			{
				tmpEdge.end = i ;
				tmpEdge.weight = matrix[oneVertex][i] ;  //处理有权图
				break ;                                  //一旦找到第一条边就退出循环
			}
		}
		return tmpEdge ;
	}
	Edge<EdgeType> NextEdge(Edge<EdgeType> oneEdge)      //避免跟上面的边重复，因此采用边来作为参数
	{
		Edge<EdgeType> tmpEdge ;
		tmpEdge.start = oneEdge.start ;
		for(int i = oneEdge.end+1; i < vertexNum; i++)   //从下一条边开始算起
		{
			if(matrix[oneEdge.start][i] != 0)
			{
				tmpEdge.end = i ;                         //找到第一条不同的边就退出循环
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
		matrix[start][end] = 0 ;             //表示没有边
											 //处理的是有向图
	}
};

#endif