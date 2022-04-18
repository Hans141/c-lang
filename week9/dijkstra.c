#include <stdio.h>
#include "week4/jrb.h"
#include "week4/jval.h"
#include "week4/dllist.h"
#include <string.h>
#include <stdlib.h>
#define INFINITIVE_VALUE 10000000
#define Max 100
int setD[Max] = {};
int setParent[Max] = {};

typedef struct
{
  JRB edges;
  JRB vertices;
} Graph;

Graph createGraph()
{
  Graph graph;
  graph.edges = make_jrb();
  graph.vertices = make_jrb();
  return graph;
}

void addVertex(Graph graph, int id, char *name)
{
  JRB node;
  JRB tree;
  node = jrb_find_int(graph.vertices, id);
  if (node == NULL)
  {
    jrb_insert_int(graph.vertices, id, new_jval_s(name));
    tree = make_jrb();
    jrb_insert_int(graph.edges, id, new_jval_v(tree));
  }
  else
    return;
}

char *getVertex(Graph graph, int id)
{
  JRB node;
  node = jrb_find_int(graph.vertices, id);
  if (node == NULL)
    return NULL;
  else
    return jval_s(node->val);
}

double getEdgeValue(Graph graph, int v1, int v2)
{
  JRB find = jrb_find_int(graph.edges, v1);
  JRB edge;
  if (find == NULL)
    return INFINITIVE_VALUE;
  JRB tree;
  tree = make_jrb();
  tree = jval_v(find->val);
  edge = jrb_find_int(tree, v2);
  if (edge == NULL)
    return INFINITIVE_VALUE;
  JRB find2 = jrb_find_int(graph.vertices, v2);
  return jval_d(find2->val);
}

void addEdge(Graph graph, int v1, int v2, double weight)
{
  JRB node, tree, node2;
  node = jrb_find_int(graph.edges, v1);
  if (node == NULL)
  {
    tree = make_jrb();
    jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    jrb_insert_int(tree, v2, new_jval_d(weight));
  }
  else
  {
    tree = make_jrb();
    tree = (JRB)jval_v(node->val);
    node2 = jrb_find_int(tree, v2);
    if (node2 == NULL)
    {
      jrb_insert_int(tree, v2, new_jval_d(weight));
    }
    node->val = new_jval_v(tree);
  }
}

int hasEdge(Graph graph, int v1, int v2)
{
  JRB node, tree;
  node = jrb_find_int(graph.edges, v1);
  if (node == NULL)
    return 0;
  else
  {
    tree = (JRB)jval_v(node->val);
    jrb_traverse(node, tree) if (v2 == jval_i(node->key)) return 1;
  }
  return 0;
}

int outdegree(Graph graph, int v, int *output)
{
  JRB node, tree;
  int total;
  node = jrb_find_int(graph.edges, v);
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

int indegree(Graph graph, int v, int *output)
{
  JRB node, tree;
  node = NULL;
  int key;
  int total;
  total = 0;
  jrb_traverse(node, graph.vertices)
  {
    key = jval_i(node->key);
    if (hasEdge(graph, key, v) == 1 && key != v)
      output[total++] = key;
  }
  return total;
}

int getAdjacentVertices(JRB graph, int v, int *output)
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
int DAG(Graph graph)
{
  int visited[1000];
  int n, output[100], i, u, v, start;
  Dllist node, stack;
  JRB vertex;

  jrb_traverse(vertex, graph.vertices)
  {
    memset(visited, 0, sizeof(visited));

    start = jval_i(vertex->key);
    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    while (!dll_empty(stack))
    {
      node = dll_last(stack);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u])
      {
        visited[u] = 1;
        n = outdegree(graph, u, output);
        for (i = 0; i < n; i++)
        {
          v = output[i];
          if (v == start) // cycle detected
            return 0;
          if (!visited[v])
            dll_append(stack, new_jval_i(v));
        }
      }
    }
  }
  return 1; // no cycle
}

void dropGraph(Graph graph)
{
  JRB node;
  jrb_traverse(node, graph.vertices)
      jrb_free_tree(jval_v(node->val));
  jrb_traverse(node, graph.edges)
      jrb_free_tree(jval_v(node->val));
}

double shortestPath(Graph g, int s, int t, int *path, int *length)
{
  double distance[1000], min, w, total;
  int previous[1000], tmp[1000];
  int n, output[100], i, u, v, start;
  Dllist ptr, queue, node;

  for (i = 0; i < 1000; i++)
    distance[i] = INFINITIVE_VALUE;
  distance[s] = 0;
  previous[s] = s;

  queue = new_dllist();
  dll_append(queue, new_jval_i(s));

  while (!dll_empty(queue))
  {
    // get u from the priority queue
    min = INFINITIVE_VALUE;
    dll_traverse(ptr, queue)
    {
      u = jval_i(ptr->val);
      if (min > distance[u])
      {
        min = distance[u];
        node = ptr;
      }
    }
    dll_delete_node(node);

    if (u == t)
      break; // stop at t

    n = outdegree(g, u, output);
    for (i = 0; i < n; i++)
    {
      v = output[i];
      w = getEdgeValue(g, u, v);
      if (distance[v] > distance[u] + w)
      {
        distance[v] = distance[u] + w;
        previous[v] = u;
      }
      dll_append(queue, new_jval_i(v));
    }
  }
  total = distance[t];
  if (total != INFINITIVE_VALUE)
  {
    tmp[0] = t;
    n = 1;
    while (t != s)
    {
      t = previous[t];
      tmp[n++] = t;
    }
    for (i = n - 1; i >= 0; i--)
      path[n - i - 1] = tmp[i];
    *length = n;
  }
  return total;
}

int main()
{
  int count, *output, i;
  Graph g = createGraph();
  int s, t, length, path[1000];
  addVertex(g, 0, "V0");
  addVertex(g, 1, "V1");
  addVertex(g, 2, "V2");
  addVertex(g, 3, "V3");
  addVertex(g, 4, "V4");
  addVertex(g, 5, "V5");
  addVertex(g, 6, "V6");
  addEdge(g, 0, 1, 1);
  addEdge(g, 2, 1, 2);
  addEdge(g, 1, 4, 3);
  addEdge(g, 2, 0, 4);
  addEdge(g, 1, 3, 3);
  addEdge(g, 1, 5, 2);
  addEdge(g, 2, 6, 1);
  addEdge(g, 5, 3, 5);
  addEdge(g, 1, 0, 1);
  addEdge(g, 4, 6, 2);
  addEdge(g, 3, 2, 5);
  double weight = shortestPath(g, 2, 4, path, &length);
  s = 2;
  t = 4;
  if (weight == INFINITIVE_VALUE)
    printf("No path between %d and %d\n", s, t);
  else
  {
    printf("Path between %d and %d:", s, t);
    for (i = 0; i < length; i++)
      printf("%4d", path[i]);
    printf("\n");
    printf("Total weight: %f\n", weight);
  }

  return 0;
}
