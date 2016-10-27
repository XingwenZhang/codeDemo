#include<iostream>
#include<iomanip>
#include<stack>
#include<queue>
#define MaxSize 30
#define Affinity 100
using namespace std;
class AdjGraph
{
public:char *vexs;
	   int **arcs;
	   int *visited,*de;
	   int vexnum,arcnum;
	   AdjGraph()
	   {
		   vexnum=arcnum=0;
		   vexs=NULL;visited=NULL;arcs=NULL;de=NULL;
	   }
	   AdjGraph(int v,int a)
	   {
		   int i,j;
		   vexnum=v;arcnum=a;de=new int[vexnum];
		   vexs=new char[vexnum];visited=new int[vexnum];
		   arcs=(int **)new int*[vexnum];
		   for(i=0;i<vexnum;i++)
		   {
			   arcs[i]=new int[vexnum];
		   }
		   for(i=0;i<vexnum;i++)
		   {
			   visited[i]=0;vexs[i]='\0';de[i]=0;
			   for(j=0;j<vexnum;j++)
			   {
				   if(i==j){arcs[i][j]=0;}
				   else{
					   arcs[i][j]=Affinity;}
			   }
		   }
	   }
	   ~AdjGraph(){}
	   int posvex(char x)
	   {
		   int i=0;
		   for(i=0;i<vexnum;i++)
		   {
			   if(vexs[i]==x)
				   break;
		   }
		   if(i<vexnum)
		   {return i;}
		   else
		   {return -1;}
	   }
	   void clearVisit()
	   {
		   int i;
		   for(i=0;i<vexnum;i++)
		   {
			   visited[i]=0;
		   }
	   }
	   bool CreateDUG()
	   {
		   cout<<"请输入顶点信息:"<<endl;
		   int i=0,a,b;char l,r;
		   for(i=0;i<vexnum;i++)
		   {cin>>vexs[i];}
		   for(i=0;i<arcnum;i++)
		   {
			   int w;
			   cout<<"输入第"<<i<<"条边依附的顶点"<<endl;
			   cin>>l>>r;
			   a=posvex(l);b=posvex(r);
			  cout<<"请输入该边的权重："<<endl;
			   cin>>w;
			   arcs[a][b]=w;arcs[b][a]=w;de[a]++;de[b]++;
		   }
		   return true;
	   }
	   int FirstAdj(int i)
	   {
		   int j=0;
		   while(j<vexnum&&arcs[i][j]==Affinity)
		   {j++;}
		   if(j<vexnum)
			   return j;
		   else
			   return -1;
	   } 
	   int SecondAdj(int i,int k)//顶点下标为i的顶点相对于k的下一个顶点,k为i的当前邻接顶点,二者都是顶点下标
	   {
		   int j=k+1;
		   while(j<vexnum&&arcs[i][j]==Affinity)
		   {j++;}
		   if(j<vexnum)
			   return j;
		   else
			   return -1;
	   }
	   void DFS(int v)
	   {
		   int w;visited[v]=1;cout<<vexs[v]<<' ';
		   for(w=FirstAdj(v);w>=0;w=SecondAdj(v,w))
		   {
			   if(!visited[w])
			   {DFS(w);}
		   }
	   }
	   void BFS(int v)
	   {
		   int u,w;;
		     queue<int> q1;
		   if(!visited[v])
		   {
			   visited[v]=1;cout<<vexs[v]<<' ';
			   q1.push(v);
			   while(!q1.empty())
			   {
				   u=q1.front();
				   q1.pop();
				   for(w=FirstAdj(v);w>=0;w=SecondAdj(v,w))
				   {
					   if(!visited[w])  
                       {  
						   visited[w]=true;
						   cout<<vexs[w]<<' ';
						   q1.push(w);
				       }
			       }
	          }
		   }
	   }
	   void DFSTraverse()
	   {
		   clearVisit();
		   int v;
		   for(v=0;v<vexnum;v++)
		   {
			   if(!visited[v])
			   {DFS(v);}
		   }
	   }
	   void BFSTraverse()
	   {
		   clearVisit();
		   int v;
		   for(v=0;v<vexnum;v++)
		   {
			   if(!visited[v])
			   {BFS(v);}
		   }
	   }
	   void show()
	   {
		   cout.setf(ios::right);
		   cout<<"该图的邻阶矩阵表示法："<<endl;
		   int  i,j;
		   for(i=0;i<vexnum;i++)
		   {
			   for(j=0;j<vexnum;j++)
			   {
				   cout<<setw(3)<<this->getweight(i,j)<<' ';
			   }cout<<endl;
		   }
	   }
	   int getweight(int s,int t)
	   {
		   if(s!=t)
		   {return arcs[s][t];}
		   else
			   return 0;
	   }
	   AdjGraph BreakCircle()
	   {cout<<"破圈法构造最小生成树："<<endl;
		   AdjGraph A(vexnum,arcnum);
		   int i,j;
		   for(i=0;i<vexnum;i++)
		   {A.vexs[i]=this->vexs[i];}
		   for(i=0;i<vexnum;i++)
		   {A.de[i]=this->de[i];
			   for(j=0;j<vexnum;j++)
			   {
				   A.arcs[i][j]=this->arcs[i][j];
				   A.arcs[j][i]=this->arcs[j][i];
			   }
		   }
		   for(i=0;i<arcnum-vexnum+1;i++)
		   {
			   A.retrive1();
			   A.retrivemax();
		   }
		   return A;
	   }
	   int finde1()
	   {
		   int i;
		   for(i=0;i<vexnum;i++)
		   {
			   if(de[i]==1&&visited[i]==0)
				   break;
		   }if(i<vexnum&&i>=0){return i;}
		   else{return -1;}
	   }
	   void retrive1()
	   {int k=-1,l=0;
		    k=finde1();
		    while(k!=-1){
			   if(k>=0&&k<vexnum)
			   {visited[k]=1;de[k]--;
				   l=FirstAdj(k);de[l]--;
			   }
			   k=finde1();
			}
	   }
	   void retrivemax()
	   {
		   int max,i,j,s=-1,t=-1;
		   max=0;
		   for(i=0;i<vexnum;i++)
		  {	   for(j=0;j<vexnum;j++)
			   {
				   if(visited[i]==0&&visited[j]==0&&arcs[i][j]!=Affinity)
				   {
				   if(max<getweight(i,j))
				   {
					   max=getweight(i,j);s=i;t=j;
				   }
				   }
			   }
		   }
		   if(s==-1&&t==-1){return;}
		   else
			   arcs[s][t]=Affinity;arcs[t][s]=Affinity;de[s]--;de[t]--;
	   }
};
void main()
{
	int i,j;
	cout<<"请输入顶点个数和边数"<<endl;
	cin>>i>>j;
	AdjGraph A1(i,j);
	A1.CreateDUG();
	A1.show();
	cout<<"深度优先遍历序列："<<endl;
	A1.DFSTraverse();cout<<endl;
	cout<<"广度优先遍历序列："<<endl;
	A1.BFSTraverse();cout<<endl;
	A1.BreakCircle().show();
	cout<<"广度优先遍历序列："<<endl;
	A1.BreakCircle().BFSTraverse();
}