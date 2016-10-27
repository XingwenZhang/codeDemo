#include <iostream>
#include<limits>
using namespace std;

#define DEFAULT_VERTEX_NUM 5
#define MAX 99999
#define MAX_EDGETYPE 99999


template<class VertexType,class EdgeType>
class Graph{
	VertexType *NodeList;  //保存顶点数据的一位数组
	EdgeType *AdjMatrix;   //保存邻接矩阵的一维数组，邻接矩阵
	                       //AdjMatrix[i*NumVertex + j] ,表示
	                       //i顶点到j顶点方向，数值表示路径长度
	int currentNode; //指着当前的节点
	int numEdge;  //图当前的边数
	int maxNumEdge; //图的最大边数
	int numVertex;  //图当前的顶点数
	int maxNumVertex; //图最大的顶点数
public:
	Graph(int );
	~Graph();
	int GetNumVertex(){return numVertex;}
	VertexType InsertVertex(const VertexType& ); //插入一个节点
	int RemoveVertex(const VertexType& ); //删除一个节点
	EdgeType InsertEdge(int i,int j,EdgeType weight); //从i向j插入一条权重为weight的边
	int RemoveEdge(int i ,int j); //移除i向j的边
	void ExpandSize();    //用于动态自增长，节点数翻倍、同时边数相应翻两倍
	EdgeType *Dijkstra(VertexType startVertexValue);
	//void Cout();
};


//测试输出
//template<class VertexType,class EdgeType>
//void Graph<VertexType, EdgeType>::Cout(){
//	cout << "NodeList 数组索引：\n";
//	cout <<"       i\\j";
//	for(int i = 0;i < numVertex;i++)
//		cout << "\t" << i << " ";
//	int cntLine = 0; //列计数
//	int cntRow = 0; //行计数
//	//cout << "\n邻接矩阵数据：\n";
//	cout << endl;
//	for(int i = 0;i < maxNumEdge;i++){
//		if( i % maxNumVertex == 0 && cntRow < numVertex )
//			cout << "\t" << cntRow++;
//		if(cntRow == numVertex && cntLine == numVertex )
//			break;
//		if(cntLine++ < numVertex && cntRow <= numVertex)
//			cout << "\t" << AdjMatrix[i] ;
//		if( (i + 1) % maxNumVertex == 0){ //每行遍历结束换行
//			cout << endl;
//			cntLine = 0;
//		}
//	}
//	cout << endl;
//	cout << "各节点的值： \n";
//	for(int i = 0;i < numVertex;i++)
//		cout << NodeList[i] << " ";
//	cout << "\n\n";
//}


//动态自增长
template<class VertexType,class EdgeType>
void Graph<VertexType, EdgeType>::ExpandSize(){
	//复制所有节点数组到扩容后的NodeList
	VertexType *tempNodeList = NodeList;
	int originMaxNumVertex = maxNumVertex;
	maxNumVertex <<= 1;
	NodeList = new VertexType[maxNumVertex];
	for(int i = 0;i < (maxNumVertex >> 1);i++)
		NodeList[i] = tempNodeList[i];
	delete []tempNodeList;
	//复制邻接边数组AdjMatrix
	EdgeType *tempAdjMatrix = AdjMatrix;
//	int originMaxNumEdge = maxNumEdge;
	maxNumEdge = maxNumVertex * maxNumVertex;
	AdjMatrix = new EdgeType[maxNumEdge];
	for(int i = 0;i < originMaxNumVertex;i++)
		for(int j = 0;j < originMaxNumVertex;j++)
			AdjMatrix[maxNumVertex * i + j] = tempAdjMatrix[originMaxNumVertex * i + j];
	//未知变量都赋为MAX表示不可达,修改对角线元素为0
	for(int i = 0;i < maxNumVertex;i++)
		for(int j = 0;j < maxNumVertex;j++){
			if(!(i < originMaxNumVertex && j < originMaxNumVertex)){
				AdjMatrix[maxNumVertex * i + j] = MAX;
			}
		}
	for(int i = originMaxNumVertex;i < maxNumVertex;i++){
		AdjMatrix[maxNumVertex * i + i] = 0;
	}
	delete []tempAdjMatrix;
}


template<class VertexType,class EdgeType>
VertexType Graph<VertexType, EdgeType>::InsertVertex(const VertexType& newVertexValue){
	if(numVertex == maxNumVertex)
		ExpandSize();
	NodeList[numVertex++] = newVertexValue;
	return newVertexValue;
}


template<class VertexType,class EdgeType>
int Graph<VertexType, EdgeType>::RemoveVertex(const VertexType& vertexValue){
	if(numVertex == 0)
		return -1;  //没有找到
	else{
		int pos = 0;
		for(;pos < numVertex;pos++){
			if(NodeList[pos] == vertexValue)
				break;
		}
		if(pos == numVertex)
			return -1;  //没有找到
		for(int i = pos;i < numVertex;i++){
			NodeList[i] = NodeList[i + 1];
		}
		for(int i = 0;i < maxNumVertex - 1;i++)
			for(int j = 0;j < maxNumVertex - 1;j++){
				int x = j >= pos ? j + 1 : j;
				int y = i >= pos ? i + 1 : i;
				AdjMatrix[maxNumVertex * i + j] = AdjMatrix[maxNumVertex * y + x];
			}
		return --numVertex;
	}
}


template<class VertexType,class EdgeType>
EdgeType Graph<VertexType, EdgeType>::InsertEdge(int i,int j,EdgeType weight){
	if(i < maxNumVertex && j < maxNumVertex && i != j)
		AdjMatrix[maxNumVertex * i + j] = weight;
	return weight;
}


template<class VertexType,class EdgeType>
int Graph<VertexType, EdgeType>::RemoveEdge(int i,int j){
	if(i < maxNumVertex && j < maxNumVertex && i != j){
		AdjMatrix[maxNumVertex * i + j] = MAX;
		numEdge--;
		return numEdge;
	}else
		return -1;
}


template<class VertexType,class EdgeType>
Graph<VertexType,EdgeType>::Graph(int maxVertexSize = DEFAULT_VERTEX_NUM){
	numVertex = 0;numEdge = 0;currentNode = 0;

	maxNumVertex = maxVertexSize > DEFAULT_VERTEX_NUM ? maxVertexSize : DEFAULT_VERTEX_NUM;
	maxNumEdge = maxNumVertex * maxNumVertex;
	AdjMatrix = new EdgeType[maxNumEdge];
	NodeList = new VertexType[maxNumVertex];

	// 对角线顶点初始化为0,非对角线初始为MAX表示不可达
	for(int i = 0;i < maxNumEdge;i++)
		AdjMatrix[i] = MAX;
	for(int i = 0;i < maxNumVertex;i++)
		AdjMatrix[i + maxNumVertex * i] = 0;
}


template<class VertexType,class EdgeType>
Graph<VertexType,EdgeType>::~Graph(){
	delete []AdjMatrix;
	delete []NodeList;
}




template<class VertexType,class EdgeType>
EdgeType* Graph<VertexType,EdgeType>::Dijkstra(VertexType startVertexValue){
	EdgeType *DijkstraPath = new EdgeType[numVertex];
	int startPos = -1;
	for(int i = 0;i < numVertex;i++){
		if(NodeList[i] == startVertexValue){
			startPos = i;
			break;
		}
	}
	if(startPos == -1) 
		return NULL;

	//记录源点到各顶点的最短路径
	for(int i = 0;i < numVertex;i++)
		DijkstraPath[i] = AdjMatrix[startPos * maxNumVertex + i];

	//isChosen数组记录顶点i是否被取出
	bool *isChosen = new bool[numVertex];
	for(int i = 0;i < numVertex;i++)
		isChosen[i] = false;

	//初始顶点加入
	isChosen[startPos] = true;

	EdgeType min;
	int nextPos;
	//修改startPos有向可达的图DijkstraGraph[]
	for(int i = 0;i < numVertex - 1;i++){
		min  = MAX_EDGETYPE;
		for(int j = 0;j < numVertex;j++){
			EdgeType weight = AdjMatrix[startPos * maxNumVertex + j];
			if(!isChosen[j]){
				if(weight < min){
					min = weight;
					nextPos = j;
				}
			}
		}
		//取走nextPos
		isChosen[nextPos] = true;
		//每次有新的点加入就更新DijkstraGraph[]
		for(int j = 0;j < numVertex;j++){
			EdgeType D_startToNext = AdjMatrix[startPos * numVertex + nextPos];
			EdgeType D_NextToJ = AdjMatrix[nextPos * numVertex + j];
			EdgeType D_startToJ = AdjMatrix[startPos * numVertex + j];
			if(D_startToNext + D_NextToJ < D_startToJ)
				DijkstraPath[j] = D_startToNext + D_NextToJ;
		}
	}
	return DijkstraPath;
}

