]#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "jrb.h"
#include "dllist.h"
#include <stdio_ext.h>
#define Max_Str 100

#define INFINITIVE_VALUE  10000000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;


Graph createGraph()
{
   Graph g; 
   g.edges = make_jrb();  
   g.vertices = make_jrb();  
   return g;
}

void addVertex(Graph g, int id, char* name)
{
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) // only add new vertex 
         jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));            
}

char *getVertex(Graph g, int id)
{
     JRB node = jrb_find_int(g.vertices, id);
     if (node==NULL) 
        return NULL;
     else                
        return jval_s(node->val);
}     



double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node==NULL)
       return INFINITIVE_VALUE;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node==NULL)
       return INFINITIVE_VALUE;
    else
       return jval_d(node->val);       
}

void addEdge(Graph graph, int v1, int v2, double weight)
{
     JRB node, tree;
     if (getEdgeValue(graph, v1, v2)==INFINITIVE_VALUE)
     {
        node = jrb_find_int(graph.edges, v1);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        } else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
     }
}

int indegree (Graph graph, int v, int* output)
{
    JRB tree, node;
    int total = 0;   
    jrb_traverse(node, graph.edges)
    {
       tree = (JRB) jval_v(node->val);
       if (jrb_find_int(tree, v))
       {
          output[total] = jval_i(node->key);
          total++;
       }                
    }
    return total;   
}

int outdegree (Graph graph, int v, int* output)
{
    JRB tree, node;
    int total;
    node = jrb_find_int(graph.edges, v);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    total = 0;   
    jrb_traverse(node, tree)
    {
       output[total] = jval_i(node->key);
       total++;                
    }
    return total;   
}

double shortestPath(Graph g, int s, int t, int* path, int*length)
{
   double distance[1000], min, w, total;
   int previous[1000], tmp[1000];
   int n, output[100], i, u, v, start;
   Dllist ptr, queue, node;

   for (i=0; i<1000; i++)
       distance[i] = INFINITIVE_VALUE;
   distance[s] = 0;
   previous[s] = s;
       
   queue = new_dllist();
   dll_append(queue, new_jval_i(s));

   while ( !dll_empty(queue) )
   {
      // get u from the priority queue   
      min = INFINITIVE_VALUE;
      //ham tim ra trong queue diem co do dai tu s den min
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
      
      if (u == t) break; // stop at t
      n = outdegree(g, u, output);
      for (i=0; i<n; i++)
      {
	//xet cac lan can v cua u
          v = output[i];
          w = getEdgeValue(g, u, v);
          if ( distance[v] > distance[u] + w ) //neu s.v > s.u thi cap nhat lai
          {    
              distance[v] = distance[u] + w;
              previous[v] = u;
          }     
          dll_append(queue, new_jval_i(v));  //cho v vao trong queue
      }
   }
   
   total = distance[t]; //tim duoc khoang cach
   
   if (total != INFINITIVE_VALUE)
   {
       tmp[0] = t;
       n = 1;              
       while (t != s)
       {
             t = previous[t];
             tmp[n++] = t;
       }
       for (i=n-1; i>=0; i--)
	 path[n-i-1] = tmp[i]; //mang path la dao lon cua mang t
       *length = n;                
   }
   return total;   
}

void dropGraph(Graph graph)
{
    JRB node, tree;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB) jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}


int menuVaLuaChon(int a,int b)
{
  int luaChon,buff;
  char c;
  printf("+-----+--------------------------------------------------+\n");
  printf("|%25s%6s%25s|\n","","MENU","");
  printf("+-----+--------------------------------------------------+\n");
  printf("|%5d|%-50s|\n",1,"case1 ");
  printf("|%5d|%-50s|\n",2,"case2 ");
  printf("|%5d|%-50s|\n",3,"case3 ");
  printf("|%5d|%-50s|\n",4,"case4 ");
  printf("|%5d|%-50s|\n",5,"Thoat");
  printf("+-----+--------------------------------------------------+\n");

  do
    {
      __fpurge(stdin);
      printf("Nhap vao lua chon cua ban:");
      buff=scanf("%d%c",&luaChon,&c);
      if(buff!=2&&c!='\n'||luaChon<a||luaChon>b) printf("Ban da nhap sai cu phap\n");
    }while(buff!=2&&c!='\n'||luaChon<a||luaChon>b);
  return luaChon;
}

void docFile(Graph g, char *tenFile)
{
  FILE *f;
  int id;
  char ten[Max_Str];
  f=fopen(tenFile,"r");
  if(f==NULL)
    {
      printf("File open failed!\n");
      return;
    }
  int n,m;
  fscanf(f,"%d %d\n",&n,&m);
  int i;
  for(i=0;i<n;i++)
    {
      fscanf(f,"%d %s\n",&id,ten);
      __fpurge(stdin);
      addVertex(g,id,strdup(ten));
    }
  int id1,id2;
  double trongSo;
  for(i=0;i<m;i++)
    {
      fscanf(f,"%d %d %lf\n",&id1,&id2,&trongSo);
      __fpurge(stdin);
      addEdge(g,id1,id2,trongSo);
      addEdge(g,id2,id1,trongSo);
    }
}

int main()
{
    int i, length, path[100], s, t;
    double w;
    Graph g = createGraph();
    JRB node,node2,node3,node4;
    int count=0;
    int id;
    JRB tree,tree2;
    double max=0.0;
    int output[100];
    int banChung[100];
   
  int thoat,luaChon;
  thoat=0;
  int thanhCong=0;
  do
    {
      luaChon= menuVaLuaChon(1,5);
      switch(luaChon)
	{
	case 1:
	  //ham1
	  docFile(g,"data.txt");
	  jrb_traverse(node,g.vertices)
	    printf("%d %s\n",jval_i(node->key),jval_s(node->val));
	    break;
	case 2:
	  //ham2
	  printf("Nhap id:");
	  scanf("%d",&id);
	  node=jrb_find_int(g.vertices,id);
	  if(node==NULL)
	    printf("Khong co id nay!\n");
	  else
	    {
	      
	      node=jrb_find_int(g.edges,id);
	      if(node==NULL)
		printf("Khong co quan he ban be\n-1\n");
	      else
		{
		  tree=jval_v(node->val);
		  jrb_traverse(node2,tree)
		    if(max<jval_d(node2->val))
		      max=jval_d(node2->val);
		  printf("%lf\n",max);

		  jrb_first(tree);
		   jrb_traverse(node3,tree)
		    if(max==jval_d(node3->val))
		      printf("%d %s\n",jval_i(node3->key),getVertex(g,jval_i(node3->key)));
		}
		
	      		
	    }
	  break;
	case 3:
	  //ham3
	  printf("Nhap vao id1:");
	  scanf("%d",&s);
	  printf("Nhap vao id2:");
	  scanf("%d",&t);
	  node=jrb_find_int(g.edges,s);
	  node2= jrb_find_int(g.edges,t);
	  if(node==NULL||node2==NULL||node==node2)
	    {
	      printf("No\n");
	      break;
	    }
	  w = shortestPath(g, s, t, path, &length);
    if (w == INFINITIVE_VALUE)
    {
         printf("No path from %s to %s\n", getVertex(g, s), getVertex(g, t));
    }else
    {
      if(getEdgeValue(g,s,t)==INFINITIVE_VALUE)
	printf("Co quan he bac cau\n");
      else
	printf("No\n");
    }
	  break;
	case 4:
	  //ham4
	   printf("Nhap vao id1:");
	  scanf("%d",&s);
	  printf("Nhap vao id2:");
	  scanf("%d",&t);
	  node=jrb_find_int(g.edges,s);
	  node2= jrb_find_int(g.edges,t);
	  if(node==NULL||node2==NULL||node==node2)
	    {
	      printf("No\n");
	      break;
	    }
	  tree=jval_v(node->val);
	  tree2=jval_v(node2->val);
	  jrb_traverse(node3,tree)
	    {
	      id=jval_i(node3->key);
	      jrb_traverse(node4,tree2)
		{
		  if(id==jval_i(node4->key))
		    {
		      banChung[count]=id;
		      count++;
		    }
		}
	    }
	  printf("So ban chung %d\n",count);
	  for(i=0;i<count;i++)
	    printf("%d %s\n",banChung[i],getVertex(g,banChung[i]));
	  break;
	case 5:
	  thoat=1;
	  break;
	}	
    }while(thoat!=1);
    
    dropGraph(g);
    printf("\n");
    // getch();   
}
