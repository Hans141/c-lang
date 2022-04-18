#include <stdio.h>
#include <stdlib.h>
#include "week4/jrb.h"
#include "week4/jval.h"
#include "week4/dllist.h"
#define Max_DoThi 100

typedef JRB Graph;

Graph createGraph()
{
  Graph graph;
  graph = make_jrb();
  return graph;
}

void addEdge(Graph graph, int v1, int v2)
{
  JRB node, tree, node2;
  node = jrb_find_int(graph, v1);
  if (node == NULL)
  {
    tree = make_jrb();
    jrb_insert_int(graph, v1, new_jval_v(tree));
    jrb_insert_int(tree, v2, new_jval_i(1));
  }
  else
  {
    tree = make_jrb();
    tree = (JRB)jval_v(node->val);
    node2 = jrb_find_int(tree, v2);
    if (node2 == NULL)
    {
      jrb_insert_int(tree, v2, new_jval_i(1));
    }
    // jrb_insert_int(tree,v2,new_jval_i(1));
    node->val = new_jval_v(tree);
  }

  node = jrb_find_int(graph, v2);
  if (node == NULL)
  {
    tree = make_jrb();
    jrb_insert_int(graph, v2, new_jval_v(tree));
    jrb_insert_int(tree, v1, new_jval_i(1));
  }
  else
  {
    tree = make_jrb();
    tree = (JRB)jval_v(node->val);
    node2 = jrb_find_int(tree, v1);
    if (node2 == NULL)
    {
      jrb_insert_int(tree, v1, new_jval_i(1));
    }
    jrb_insert_int(tree, v1, new_jval_i(1));
    node->val = new_jval_v(tree);
  }
  // addEdge(graph,v2,v1);
}

int getAdjacentVertices(Graph graph, int v, int *output)
{
  JRB node, tree;
  int total;
  node = jrb_find_int(graph, v);
  if (node == NULL)
    return 0;
  else
  {
    tree = (JRB)jval_v(node->val);
    total = 0;
    jrb_traverse(node, tree)
        output[total++] = jval_i(node->key);
    return total;
  }
}

void dropGraph(Graph graph)
{
  JRB node;
  jrb_traverse(node, graph)
      jrb_free_tree(jval_v(node->val));
}

void BFS(Graph graph, int start, int stop, void (*func)(int))
{
  int visited[1000] = {};
  int n, output[100], i, u, v;
  Dllist node, queue;

  queue = new_dllist();
  dll_append(queue, new_jval_i(start));

  while (!dll_empty(queue))
  {
    node = dll_first(queue);
    u = jval_i(node->val);
    dll_delete_node(node);
    if (!visited[u])
    {
      func(u);
      visited[u] = 1;
      if (u == stop)
        return;
      n = getAdjacentVertices(graph, u, output);
      for (i = 0; i < n; i++)
      {
        v = output[i];
        if (!visited[v])
          dll_append(queue, new_jval_i(v));
      }
    }
  }
}

void DFS(Graph graph, int start, int stop, void (*func)(int))
{
  int visited[1000] = {};
  int n, output[100], i, u, v;
  Dllist node, stack;

  stack = new_dllist();
  dll_append(stack, new_jval_i(start));

  while (!dll_empty(stack))
  {
    node = dll_last(stack);
    u = jval_i(node->val);
    dll_delete_node(node);
    if (!visited[u])
    {
      func(u);
      visited[u] = 1;
      if (u == stop)
        return;
      n = getAdjacentVertices(graph, u, output);
      for (i = 0; i < n; i++)
      {
        v = output[i];
        if (!visited[v])
          dll_append(stack, new_jval_i(v));
      }
    }
  }
}

void printVertex(int v)
{
  printf("%4d", v);
}

int main()
{
  Graph g = createGraph();
  addEdge(g, 0, 1);
  addEdge(g, 1, 2);
  addEdge(g, 1, 3);
  addEdge(g, 2, 3);
  addEdge(g, 2, 4);
  addEdge(g, 4, 5);
  printf("\nBFS: start from node 1 to   5 : ");
  BFS(g, 1, 4, printVertex);
  printf("\nBFS: start from node 1 to all : ");
  BFS(g, 1, -1, printVertex);
  printf("\nDFS: start from node 2 to   5 : ");
  DFS(g, 1, 4, printVertex);
  printf("\nDFS: start from node 1 to all : ");
  DFS(g, 1, -1, printVertex);
  dropGraph(g);
  // getch();
  printf("\n");
}
