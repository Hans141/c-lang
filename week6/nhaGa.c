#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include  "week4/jrb.h"
#include "week4/jval.h"
#define Max_Ga 100
#define Max_String 30
#define Max_GaTrenTram 20

typedef JRB Graph;

typedef struct
{
  char kiHieu[Max_String];
  char ten[Max_String];
}Ga;

Graph createGraph()
{
  Graph graph;
  graph=make_jrb();
  return graph;
}

void addEdge(Graph graph, char* v1,char* v2)
{
  JRB node,tree,node2;
  node=jrb_find_str(graph,v1);
  if(node==NULL)
    {
      tree=make_jrb();
      jrb_insert_str(graph,v1,new_jval_v(tree));
      jrb_insert_str(tree,v2,new_jval_i(1));
    }
  else
    {
      tree=make_jrb();
      tree=(JRB)jval_v(node->val);
      node2=jrb_find_str(tree,v2);
      if(node2==NULL)
	{
	  jrb_insert_str(tree,v2,new_jval_i(1));
	}
      //jrb_insert_str(tree,v2,new_jval_i(1));
      node->val=new_jval_v(tree);
    }
  node=jrb_find_str(graph,v2);
  if(node==NULL)
    {
      tree=make_jrb();
      jrb_insert_str(graph,v2,new_jval_v(tree));
      jrb_insert_str(tree,v1,new_jval_i(1));
    }
  else
    {
      tree=make_jrb();
      tree=(JRB)jval_v(node->val);
      node2=jrb_find_str(tree,v1);
      if(node2==NULL)
	{
	  jrb_insert_str(tree,v1,new_jval_i(1));
	}
      node->val=new_jval_v(tree);
    }
  // addEdge(graph,v2,v1);
  //printf("Da add thanh cong\n");
}

int getAdjacentVerties(Graph graph,char *v,char* output[])
{
  JRB node,tree;
  int total;
  node=jrb_find_str(graph,v);
  if(node==NULL)
    return 0;
  else
    {
      tree=(JRB) jval_v(node->val);
      total=0;
      jrb_traverse(node,tree)
	output[total++]=(char*)jval_s(node->key);
      return total;
    }
}

void dropGraph(Graph graph)
{
  JRB node;
  jrb_traverse(node, graph)
    jrb_free_tree(jval_v(node->val));
}


Ga LayGaTuFile(char *str)
{
  Ga ga;
  const char s[2] = "=";
  char *token;
   
   //lay token dau tien
  //printf("%s\n",str);
   token = strtok(str, s);
   strcpy(ga.kiHieu,token);
   strcpy(ga.ten,strtok(NULL,s));
   // printf("%s:%s\n",ga.kiHieu,ga.ten);
   return ga;
}


int timSoGa(Ga ga[],char* kiHieu,int soGa)
{
  int i;
  for(i=0;i<soGa;i++)
    {
      if(strcmp(ga[i].kiHieu,kiHieu)==0)
	return i;
    }
  return -1;
}

void DocFileCacTramM(Graph graph,char *str,Ga ga[],int soGa)
{
  int i;
  int n;
  int dayKiHieu[Max_GaTrenTram];
  const char s[2]= "=";
  const char ss[2]= " ";
  char *token;
  i=0;
  token=strtok(str,s);
  str=strtok(NULL,s);
  //printf("%s\n",str);
  token=strtok(str,ss);
  dayKiHieu[i]=timSoGa(ga,token,soGa);
  i++;
  while(token != NULL)
    {
      token = strtok(NULL, ss);
      if(token==NULL)
	break;
      dayKiHieu[i]=timSoGa(ga,token,soGa);
      addEdge(graph,ga[dayKiHieu[i]].ten,ga[dayKiHieu[i-1]].ten);
      
      i++;
    }
}

int main()
{
  Graph graph;
  char* output[Max_Ga];
  Ga ga[Max_Ga];
  FILE *fptr;
  char str[Max_String];
  int i,n,soGa;
  i=0;

  graph=createGraph();
  
  fptr=fopen("file.txt","r");
  fgets(str,100,fptr);
  //printf("%s",str);
  
  while(1)
    {
      fgets(str,100,fptr);
      if(strcmp(str,"Line:\n") !=0)
	{
	  str[strlen(str)-1]='\0';
	  //printf("%s\n",str);
	  ga[i]=LayGaTuFile(str);
	  // printf("%d,%s:%s\n",i,ga[i].kiHieu,ga[i].ten);
	  i++;
	}
      else
	{
	  soGa=i;
	  break;
	}
    }
  while(fgets(str,100,fptr)!=NULL)
    {
      // fgets(str,100,fptr);
      str[strlen(str)-1]='\0';
      DocFileCacTramM(graph,str,ga,soGa);
    }
  
  printf("Ban muon tim cac tap sat nha ga nao:");
  __fpurge(stdin);
  gets(str);
  __fpurge(stdin);
  if(str[strlen(str)-1]=='\n')
    str[strlen(str)-1]='\0';
  // printf("%s\n",str);
  n=getAdjacentVerties(graph,str,output);
  printf("Cac nha ga gan ke:\n");
  if(n==0)
    printf("khong co\n");
  else
    {
      for(i=0;i<n;i++)
	printf("%s\n",output[i]);
    }
}
