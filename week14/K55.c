#include <stdio.h>
#include "jrb.h"
#include "jval.h"
#include "dllist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#define Max_String 1000
#define INFINITIVE_VALUE 100000
typedef struct
{
  JRB edges;
  JRB vertices;
}Graph;

Graph createGraph()
{
  Graph graph;
  graph.edges=make_jrb();
  graph.vertices=make_jrb();
  return graph;
}

void addVertex(Graph graph,int id,char *name)
{
  JRB node;
  JRB tree;
  node=jrb_find_int(graph.vertices,id);
  if(node==NULL)
    {
      jrb_insert_int(graph.vertices,id,new_jval_s(name));
      tree=make_jrb();
      jrb_insert_int(graph.edges,id,new_jval_v(tree));
    }
  else return;
}

char *getVertex(Graph graph,int id)
{
  JRB node;
  node=jrb_find_int(graph.vertices,id);
  if(node==NULL)
    return NULL;
  else return jval_s(node->val);
}

void addEdge(Graph graph,int v1,int v2, int value)
{
  JRB node,tree,node2;
   node=jrb_find_int(graph.edges,v1);
  if(node==NULL)
    {
      tree=make_jrb();
      jrb_insert_int(graph.edges,v1,new_jval_v(tree));
      jrb_insert_int(tree,v2,new_jval_i(value));
    }
  else
    {
      tree=make_jrb();
      tree=(JRB)jval_v(node->val);
      node2=jrb_find_int(tree,v2);
      if(node2==NULL)
	{
	  jrb_insert_int(tree,v2,new_jval_i(value));
	}
      // jrb_insert_int(tree,v2,new_jval_i(1));
      node->val=new_jval_v(tree);
    }
}

int hasEdge(Graph graph,int v1,int v2)
{
  JRB node,tree;
  node=jrb_find_int(graph.edges,v1);
  if(node==NULL)
    return 0;
  else
    {
      tree=(JRB) jval_v(node->val);
      jrb_traverse(node,tree)
	if(v2==jval_i(node->key))
	   return 1;
    }
  return 0;
}


int getEdgeValue(Graph graph, int v1, int v2)
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
       return jval_i(node->val);       
}

int outdegree(Graph graph,int v,int* output)
{
  JRB node,tree;
  int total;
  node=jrb_find_int(graph.edges,v);
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

int indegree(Graph graph,int v,int*output)
{
  JRB node,tree;
  node=NULL;
  int key;
  int total;
  total=0;
  jrb_traverse(node,graph.vertices)
    {
      key = jval_i(node->key);
      if(hasEdge(graph,key,v)==1&&key!=v)
	output[total++]=key;
    }
  return total;
}

int getAdjacentVertices(JRB graph,int v,int *output)
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
    
       while ( !dll_empty(stack) )
       {
          node = dll_last(stack);
          u = jval_i(node->val);
          dll_delete_node(node);
          if (!visited[u])
          {
              visited[u] = 1;
              n = outdegree(graph, u, output);
              for (i=0; i<n; i++)
              {
                  v = output[i];
                  if ( v == start ) // cycle detected 
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

void deleteEdge(Graph graph, int v1,int v2)
{
  JRB node,node2;
  if(hasEdge(graph,v1,v2)==0)
    return;
  else
    {
      JRB tree;
      node=jrb_find_int(graph.edges,v1);
      tree=(JRB) jval_v(node->val);
      node2=jrb_find_int(tree,v2);
      jrb_delete_node(node2);
    }
}

int topologicalSort(Graph g, int output[], int* n, int ketThuc)
{
  Dllist queue;
  JRB node,node2;
  int OUT[100],OUT2[100];
  int totalOut;
  int t;
  int giaTri;
  int tong=0;
  t=0;
  Dllist dlltmp;
  queue=new_dllist();
  //duyet va cho tat ca nhung indegree=0 vao queue
  jrb_traverse(node,g.vertices)
    if(indegree(g,jval_i(node->key),OUT)==0)
      dll_append(queue,node->key);
  
  while(!dll_empty(queue))
    {
      dlltmp=dll_first(queue); 
      output[t]=jval_i(dlltmp->val);
      t++;
      if(output[t]==ketThuc) break;

      totalOut=outdegree(g,jval_i(dlltmp->val),OUT);
      giaTri=jval_i(dlltmp->val);
       dll_delete_node(dlltmp);
      for(int i=0;i<totalOut;i++)
	{
	  // node2=jrb_find_int(g.edges,OUT[i]);
	  deleteEdge(g,giaTri,OUT[i]);
	  if(indegree(g,OUT[i],OUT2)==0)
	    dll_append(queue,new_jval_i(OUT[i]));
	}
    }
  *n=t;
  return tong;
}

int layID(char* str)
{
  return atoi(&str[1]);
}

int docFile(char *tenFile, Graph g)
{
  FILE *f;
  char str[Max_String];
  char ten[Max_String];
  char ten2[Max_String];
  int soDinh=0;
  char *token, *token2;
  char s[2]=" ";
  char s2[2]= "-";
  int i;
  int j;
  f=fopen(tenFile,"r");
  if(f==NULL)
    {
      printf("File open failed\n");
      exit(1);
    }
  while(!feof(f))
    {
      fgets(str,Max_String,f);
      if(strlen(str)==0) break;
      str[strlen(str)-1]=0;
      soDinh++;
      for(i=0;i<strlen(str);i++)
	if(str[i]==':') break;
      strncpy(ten,str,i);
      ten[i]=0;
      //printf("%s %s\n",ten,str);
      strcpy(str,&str[i+1]);
      if(ten[0]!='A') break;
      //    printf("%d %s\n",layID(ten),ten);
      addVertex(g,layID(ten),strdup(ten));
      // printf("%d %s\n",layID(ten),getVertex(g,layID(ten)));
      if(strlen(str)==0)
	continue;
      
       token = strtok(str, s);
       while( token != NULL )
	 {

	   // printf("token cua ten( %s) %s\n",ten, token);
	   for(j=0;j<strlen(token);j++)
	     if(token[j]=='-')
	       break;
	   strncpy(ten2,token,j);
	   ten2[j]=0;
	   strcpy(token,&token[j+1]);
	   addEdge(g,layID(ten2),layID(ten),atoi(token));
	   // printf("%s %s %d\n",getVertex(g,layID(ten)),ten2,atoi(token));
	   token = strtok(NULL, s);
	 }
       // printf("%d %s\n",layID(ten),ten);
    }
   
  return soDinh-1;
  
}

int main()
{
  int i;
  int n;
  int output[100];
  Graph g = createGraph();
  Graph g2= createGraph();
  int soDinh;
  char tenDinh[Max_String];
  JRB node;
  int tong;
  soDinh=docFile("file.txt",g);
  docFile("file.txt",g2);

    jrb_traverse(node,g.vertices)
    printf("%d %s\n",jval_i(node->key),getVertex(g,jval_i(node->key)));
 if (!DAG(g))
   {
     printf("Can not make topological sort\n");
     return 1;
   }
 printf("So cong viec: %d\n",soDinh);
 int count =0;
 jrb_traverse(node,g.vertices)
   {
     count=count + outdegree(g,jval_i(node->key),output);
   }
 printf("So cung : %d\n",count);
 int thoat =0;
 int nhapLai;
 int *output2;
 int soCV;
 do
   {
     output2 =(int*) malloc(sizeof(int)*100);
     printf("Nhap vao dinh:");
     __fpurge(stdin);
     scanf("%s",tenDinh);
     tenDinh[strlen(tenDinh)]=0;
     __fpurge(stdin);
     if(tenDinh[0]!='A')
       {
	 printf("Khong co dinh nay\n");
	 printf("Nhap lai? (1/0)");
	 scanf("%d",&nhapLai);
	 if(nhapLai==1)
	   thoat=0;
	 else
	   thoat=1;
       }
     else
        if(jrb_find_int(g.vertices,layID(tenDinh))==NULL)
       {
	 printf("Khong co dinh nay\n");
	 printf("Nhap lai? (1/0)");
	 scanf("%d",&nhapLai);
	 if(nhapLai==1)
	   thoat=0;
	 else
	   thoat=1;
       }
       else
	 {
	   soCV=indegree(g,layID(tenDinh),output2);
	   printf("So luong cong viec can lam truoc: %d\n",soCV);
	   for(int z=0;z<soCV;z++)
	     printf("%-5s",getVertex(g,output2[z]));
	   printf("\n");
	   
	   tong=topologicalSort(g2,output,&n,layID(tenDinh));
	   if(n==0)
	     printf("Khong co viec lam truoc\n");
	   else
	     {
	   printf("The topological order:\n");
	   // printf("%d\n",n);
	   for (i=0; i<n; i++)
	     printf("%s\n", getVertex(g,output[i]));
	     }
	   printf("Toi thieu can: %d\n", tong);
	   
	    printf("Nhap lai? (1/0)");
	    scanf("%d",&nhapLai);
	    if(nhapLai==1)
	      thoat=0;
	    else
	      thoat=1;
	    free(output2);
	 }
     
   }while(thoat!=1);
 topologicalSort(g,output,&n,-1);
  printf("The topological order:\n");
  for (i=0; i<n; i++)
  printf("%s\n", getVertex(g,output[i]));

  if (!DAG(g))
   {
     printf("Co chu trinh\n");
     return 1;
   }
  else
    printf("Khong co chu trinh\n");
}
