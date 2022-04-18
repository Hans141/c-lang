#include <stdio.h>
#include <stdlib.h>
#include  "week4/jrb.h"
#include "week4/jval.h"

typedef JRB Graph;

Graph createGraph()
{
  Graph graph;
  graph=make_jrb();
  return graph;
}

void addEdge(Graph graph, int v1,int v2)
{
  JRB node,tree,node2;
  node=jrb_find_int(graph,v1);
  if(node==NULL)
    {
      tree=make_jrb();
      jrb_insert_int(graph,v1,new_jval_v(tree));
      jrb_insert_int(tree,v2,new_jval_i(1));
    }
  else
    {
      tree=make_jrb();
      tree=(JRB)jval_v(node->val);
      node2=jrb_find_int(tree,v2);
      if(node2==NULL)
	{
	  jrb_insert_int(tree,v2,new_jval_i(1));
	}
      // jrb_insert_int(tree,v2,new_jval_i(1));
      node->val=new_jval_v(tree);
    }

  node=jrb_find_int(graph,v2);
  if(node==NULL)
    {
      tree=make_jrb();
      jrb_insert_int(graph,v2,new_jval_v(tree));
      jrb_insert_int(tree,v1,new_jval_i(1));
    }
  else
    {
      tree=make_jrb();
      tree=(JRB)jval_v(node->val);
      node2=jrb_find_int(tree,v1);
      if(node2==NULL)
	{
	  jrb_insert_int(tree,v1,new_jval_i(1));
	}
      jrb_insert_int(tree,v1,new_jval_i(1));
      node->val=new_jval_v(tree);
    }
  // addEdge(graph,v2,v1);
}

int getAdjacentVerties(Graph graph,int v,int *output)
{
  JRB node,tree;
  int total;
  node=jrb_find_int(graph,v);
  if(node==NULL)
    return 0;
  else
    {
      tree=(JRB) jval_v(node->val);
      total=0;
      jrb_traverse(node,tree)
	output[total++]=jval_i(node->key);
      return total;
    }
}

void dropGraph(Graph graph)
{
  JRB node;
  jrb_traverse(node, graph)
    jrb_free_tree(jval_v(node->val));
}

int main()
{
  Graph graph;
  int n,output[10];
  graph=createGraph();
  addEdge(graph,0,1);
  addEdge(graph,0,2);
  addEdge(graph,0,6);
  addEdge(graph,0,5);
  addEdge(graph,5,3);
  addEdge(graph,5,4);
  addEdge(graph,3,4);
  addEdge(graph,6,4);
  addEdge(graph,7,8);
  addEdge(graph,9,10);
  addEdge(graph,9,11);
  addEdge(graph,9,12);
  addEdge(graph,11,12);
  for(int j=0;j<13;j++)
    {
  n=getAdjacentVerties(graph,j,output);
  if(n==0)
    printf("Khong co\n");
  else
    for(int i=0;i<n;i++)
      printf("%5d",output[i]);
  
  printf("\n");
    
    }
  
  n=getAdjacentVerties(graph,19,output);
  if(n==0)
    printf("Khong co\n");
  else
    for(int i=0;i<n;i++)
      printf("%5d",output[i]);
  printf("\n");
}

