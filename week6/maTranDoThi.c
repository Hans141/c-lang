#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
int main()
{
    int i, n, output[100];
    Graph g = createGraph(100);
    addEdge(g, 0, 1);
    addEdge(g, 0, 2);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    n = getAdjacentVertices (g, 2, output);
    // printf("\n%d\n\n",n);
    if (n==0) printf("Khong co dinh ke nut 1\n");
    else {   
      printf("Cac dinh ke nut 2:");
       for (i=0; i<n; i++) printf("%5d", output[i]);
    }
    printf("\n");
    dropGraph(g);
}
