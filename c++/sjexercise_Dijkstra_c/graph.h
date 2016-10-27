#include <iostream>
#include<limits>
using namespace std;

#define DEFAULT_VERTEX_NUM 5
#define MAX 99999
#define MAX_EDGETYPE 99999


template<class VertexType,class EdgeType>
class Graph{
	VertexType *NodeList;  //���涥�����ݵ�һλ����
	EdgeType *AdjMatrix;   //�����ڽӾ����һά���飬�ڽӾ���
	                       //AdjMatrix[i*NumVertex + j] ,��ʾ
	                       //i���㵽j���㷽����ֵ��ʾ·������
	int currentNode; //ָ�ŵ�ǰ�Ľڵ�
	int numEdge;  //ͼ��ǰ�ı���
	int maxNumEdge; //ͼ��������
	int numVertex;  //ͼ��ǰ�Ķ�����
	int maxNumVertex; //ͼ���Ķ�����
public:
	Graph(int );
	~Graph();
	int GetNumVertex(){return numVertex;}
	VertexType InsertVertex(const VertexType& ); //����һ���ڵ�
	int RemoveVertex(const VertexType& ); //ɾ��һ���ڵ�
	EdgeType InsertEdge(int i,int j,EdgeType weight); //��i��j����һ��Ȩ��Ϊweight�ı�
	int RemoveEdge(int i ,int j); //�Ƴ�i��j�ı�
	void ExpandSize();    //���ڶ�̬���������ڵ���������ͬʱ������Ӧ������
	EdgeType *Dijkstra(VertexType startVertexValue);
	//void Cout();
};


//�������
//template<class VertexType,class EdgeType>
//void Graph<VertexType, EdgeType>::Cout(){
//	cout << "NodeList ����������\n";
//	cout <<"       i\\j";
//	for(int i = 0;i < numVertex;i++)
//		cout << "\t" << i << " ";
//	int cntLine = 0; //�м���
//	int cntRow = 0; //�м���
//	//cout << "\n�ڽӾ������ݣ�\n";
//	cout << endl;
//	for(int i = 0;i < maxNumEdge;i++){
//		if( i % maxNumVertex == 0 && cntRow < numVertex )
//			cout << "\t" << cntRow++;
//		if(cntRow == numVertex && cntLine == numVertex )
//			break;
//		if(cntLine++ < numVertex && cntRow <= numVertex)
//			cout << "\t" << AdjMatrix[i] ;
//		if( (i + 1) % maxNumVertex == 0){ //ÿ�б�����������
//			cout << endl;
//			cntLine = 0;
//		}
//	}
//	cout << endl;
//	cout << "���ڵ��ֵ�� \n";
//	for(int i = 0;i < numVertex;i++)
//		cout << NodeList[i] << " ";
//	cout << "\n\n";
//}


//��̬������
template<class VertexType,class EdgeType>
void Graph<VertexType, EdgeType>::ExpandSize(){
	//�������нڵ����鵽���ݺ��NodeList
	VertexType *tempNodeList = NodeList;
	int originMaxNumVertex = maxNumVertex;
	maxNumVertex <<= 1;
	NodeList = new VertexType[maxNumVertex];
	for(int i = 0;i < (maxNumVertex >> 1);i++)
		NodeList[i] = tempNodeList[i];
	delete []tempNodeList;
	//�����ڽӱ�����AdjMatrix
	EdgeType *tempAdjMatrix = AdjMatrix;
//	int originMaxNumEdge = maxNumEdge;
	maxNumEdge = maxNumVertex * maxNumVertex;
	AdjMatrix = new EdgeType[maxNumEdge];
	for(int i = 0;i < originMaxNumVertex;i++)
		for(int j = 0;j < originMaxNumVertex;j++)
			AdjMatrix[maxNumVertex * i + j] = tempAdjMatrix[originMaxNumVertex * i + j];
	//δ֪��������ΪMAX��ʾ���ɴ�,�޸ĶԽ���Ԫ��Ϊ0
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
		return -1;  //û���ҵ�
	else{
		int pos = 0;
		for(;pos < numVertex;pos++){
			if(NodeList[pos] == vertexValue)
				break;
		}
		if(pos == numVertex)
			return -1;  //û���ҵ�
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

	// �Խ��߶����ʼ��Ϊ0,�ǶԽ��߳�ʼΪMAX��ʾ���ɴ�
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

	//��¼Դ�㵽����������·��
	for(int i = 0;i < numVertex;i++)
		DijkstraPath[i] = AdjMatrix[startPos * maxNumVertex + i];

	//isChosen�����¼����i�Ƿ�ȡ��
	bool *isChosen = new bool[numVertex];
	for(int i = 0;i < numVertex;i++)
		isChosen[i] = false;

	//��ʼ�������
	isChosen[startPos] = true;

	EdgeType min;
	int nextPos;
	//�޸�startPos����ɴ��ͼDijkstraGraph[]
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
		//ȡ��nextPos
		isChosen[nextPos] = true;
		//ÿ�����µĵ����͸���DijkstraGraph[]
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

