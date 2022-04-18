#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "queueDoThi.h"
#define Max_DoThi 100

#define MaxLength 100
typedef int ElementType;

typedef struct
{
  ElementType Elements[MaxLength];//Store the elements
  int Front, Rear;
} Queue;


void MakeNull_Queue(Queue *Q)
{
  Q->Front=-1;
  Q->Rear=-1;
}

int Empty_Queue(Queue Q)
{
  return Q.Front==-1;
}

int Full_Queue(Queue Q)
{
  return (Q.Rear-Q.Front+1)==MaxLength;
}

void EnQueue(ElementType X,Queue *Q)
{
  if(!Full_Queue(*Q))
    {
      if (Empty_Queue(*Q))
	Q->Front=0;
      Q->Rear=Q->Rear+1;
      Q->Elements[Q->Rear]=X;
    }
  else printf("Queue is full\n");
}

ElementType DeQueue(Queue *Q)
{
  ElementType data;
  data=Q->Elements[Q->Front];
  if(!Empty_Queue(*Q))
    {



      Q->Front=Q->Front+1;
      if (Q->Front > Q->Rear)
	MakeNull_Queue(Q);// Queue trở thành rỗng
    }
  else printf("Queue is empty!\n");
  return data;
} 

typedef struct
{
  int *matrix;
  int sizemax;
}Graph;

Graph createGraph(int sizemax)
{
  Graph graph;
  graph.matrix=(int*) malloc(sizeof(int)*sizemax*sizemax);
  for(int i=0;i<sizemax*sizemax;i++)
    graph.matrix[i]=0;
  graph.sizemax=sizemax;
  return graph;
}

void addEdge(Graph graph, int v1, int v2)
{
  graph.matrix[v1* graph.sizemax+v2]=1;
  graph.matrix[v2* graph.sizemax+v1]=1;
}

int adjacent(Graph graph,int v1,int v2)
{
  return graph.matrix[v1*graph.sizemax+v2]==1;
  // return graph.matrix[v2*graph.sizemax+v1]==1;
  
  
}

int getAdjacentVertices(Graph graph, int vertix,int *output)
{
  int i,k;
  k=0;
  for(i=0;i<graph.sizemax;i++)
    {
      if(graph.matrix[vertix*graph.sizemax+i]==1)
	{
	output[k]=i;
	k++;
	}
    }
  return k;
}

void dropGraph(Graph graph)
{
  free(graph.matrix);
  graph.matrix=NULL;
}

void BFS_DuyetHet(Graph graph, int s, void (*ham)(int))
{
  int visited[Max_DoThi];
  int node;
  int i;
  int output[Max_DoThi];
  for(i=0;i<graph.sizemax;i++)
    visited[i]=0;
  Queue q;
  MakeNull_Queue(&q);
  EnQueue(s,&q);
  while(!Empty_Queue(q))
    {
      node=DeQueue(&q);
      if(visited[node]==0)
	{
	  ham(node);
	  //  printf("%d\n",node);
	  visited[node]=1;
	  for(int j=0;j<getAdjacentVertices(graph,node,output);j++)
	    {
	      if(visited[output[j]]==0)
		EnQueue(output[j],&q);
	    }
	}
    }
}

void BFS(Graph graph, int start, int stop, void (*ham)(int))
{
  int visited[Max_DoThi];
  int node;
  int i;
  int output[Max_DoThi];
  for(i=0;i<graph.sizemax;i++)
    visited[i]=0;
  Queue q;
  MakeNull_Queue(&q);
  EnQueue(start,&q);
  while(!Empty_Queue(q))
    {
      node=DeQueue(&q);
      if(visited[node]==0)
	{
	  //printf("%d\n",node);
	  ham(node);
	  visited[node]=1;
	  if( stop!=-1 && visited[stop]==1) break;
	  for(int j=0;j<getAdjacentVertices(graph,node,output);j++)
	    {
	      if(visited[output[j]]==0)
		EnQueue(output[j],&q);
	    }
	}
    }
}

void printVertex(int v)
{
  printf("%4d",v);
}



int main()
{
    Graph g = createGraph(100);
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);
    printf("\nBFS: start from node 1 to 2 : ");
    BFS(g, 1, 2, printVertex);
    printf("\nBFS: start from node 1 to all : ");
    BFS(g, 1, -1, printVertex);
    printf("\n"); 
}
