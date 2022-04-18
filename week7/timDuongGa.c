#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include  "jrb.h"
#include "jval.h"
#include "dllist.h"
#define Max_DoThi 100
#define Max_Ga 100
#define Max_String 1000
#define Max_GaTrenTram 20

typedef JRB Graph;

typedef struct
{
  char kiHieu[Max_String];
  char ten[Max_String];
}Ga;

Ga ga[Max_Ga];
int tongSoGa=0;


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

int getAdjacentVertices(Graph graph,int v,int *output)
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

void BFS(Graph graph, int start, int stop, void (*func)(int))
{
   int visited[1000] = {};
   int n, output[100], i, u, v;
   Dllist node, queue;
   
   queue = new_dllist();
   dll_append(queue, new_jval_i(start));

   while ( !dll_empty(queue) )
   {
      node = dll_first(queue);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          func(u);
          visited[u] = 1;
          if ( u == stop ) return;           
          n = getAdjacentVertices(graph, u, output);
          for (i=0; i<n; i++)
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

   while ( !dll_empty(stack) )
   {
      node = dll_last(stack);
      u = jval_i(node->val);
      dll_delete_node(node);
      if (!visited[u]) 
      {
          func(u);
          visited[u] = 1;
          if ( u == stop ) return;           
          n = getAdjacentVertices(graph, u, output);
          for (i=0; i<n; i++)
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
  printf("%-15s",ga[v].ten);
}

int timIDbyKiHieu(char* kiHieu,int soGa)
{
  int i;
  for(i=0;i<soGa;i++)
    {
      if(strcmp(ga[i].kiHieu,kiHieu)==0)
	return i;
    }
  return -1;
}

int timIDbyTenGa(char* ten,int soGa)
{
  int i;
  for(i=0;i<soGa;i++)
    {
      if(strcmp(ga[i].ten,ten)==0)
	return i;
    }
  return -1;
}

void main() {
    Graph graph = createGraph();
    char str[Max_String];
    char *token,*token1,*token2;
    char s1[2] = "=";
    char s2[2] = " ";
    int danhDau = 0;
    FILE *fptr = fopen("file.txt", "r");
    if (fptr == NULL) {
        printf("Khong mo file duoc\n");
        return;
    } else {
        while (!feof(fptr)) {
	  fgets(str,sizeof(str), fptr);
          str[strlen(str) - 1] ='\0';
	  // printf("%s\n %ld\n",str,strlen(str));
	  if (strcmp(str, "Station:") == 0)
	    {
                danhDau = 1;
                continue;
            }
	  if (strcmp(str, "Line:") == 0)
	    {
                danhDau = 2;
                continue;
            }
	  if (danhDau == 1)
	    {
                token = strtok(str,s1);
                strcpy(ga[tongSoGa].kiHieu, token);
                token = strtok(NULL, s1);
                strcpy(ga[tongSoGa].ten, token);
                tongSoGa++;
            }
	  if (danhDau == 2)
	    {
                token = strtok(str, s1);
                token1 = strtok(NULL, s2);
                token2 = strtok(NULL, s2);
                while (token1 != NULL && token2 != NULL)
		  {
		    int index1 = timIDbyKiHieu(token1,tongSoGa);
                    int index2 =timIDbyKiHieu(token2,tongSoGa);
                    addEdge(graph, index1, index2);
		    printf("Da add %s va %s\n",ga[index1].ten,ga[index2].ten);
                    token1 = token2;
                    token2 = strtok(NULL, s2);
		  }
            }
        }
    }
    fclose(fptr);
    
    printf("BFS: get from S5 to S8: \n");
    BFS(graph, timIDbyKiHieu("S5", tongSoGa),timIDbyKiHieu("S8", tongSoGa),printVertex);
    printf("\n");
    
    printf("DFS: get from S5 to S8: \n");
    DFS(graph, timIDbyKiHieu("S5", tongSoGa),timIDbyKiHieu("S8", tongSoGa),printVertex);
    printf("\n");
}
