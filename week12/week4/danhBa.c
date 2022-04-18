#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "jval.h"
#include "jrb.h"
#include <string.h>
#define MaxName 20

JRB loadFile(char* tenFile)
{
  FILE *fptr;
  char ten[MaxName];
  long sdt;
  JRB tmp,book;
  book=make_jrb();
  fptr=fopen(tenFile,"r");
  while(!feof(fptr))
    {
      fscanf(fptr,"%s\t%ld\n",ten,&sdt);
      jrb_insert_str(book,strdup(ten),new_jval_l(sdt));
    }

    jrb_traverse(tmp,book)
  printf("%s %ld\n",jval_s(tmp->key),jval_l(tmp->val));
    return book;
}

void saveFile(char* tenFile,JRB book)
{
  JRB node;
  FILE *fptr;
  char *ten;
  long sdt;
  fptr=fopen(tenFile,"w");
  jrb_traverse(node,book)
    {
      strcpy(ten,jval_s(node->key));
      sdt=jval_l(node->val);
      fprintf(fptr,"%s\t%ld\n",ten,sdt);
    }
}

int main()
{
  JRB tmp,book;
  char name[MaxName];
  long sdt;
  int n;
  book=make_jrb();
  book=loadFile("danhba.txt");   
   
  printf("Ban muon nhap bao nhieu nguoi:");
  scanf("%d",&n);
  for(int i=0;i<n;i++)
    {
      printf("Nguoi %d\n",i+1);
      printf("Ten:");
      __fpurge(stdin);
      gets(name);
      __fpurge(stdin);
      printf("SDT:");
      scanf("%ld",&sdt);
      
      tmp=jrb_find_str(book,name);
      if(tmp!=NULL)
	tmp->val=new_jval_l(sdt);
      else
	jrb_insert_str(book,strdup(name),new_jval_l(sdt));
    }

    saveFile("danhba.txt",book);

  printf("\nDanh sach:\n");
  jrb_traverse(tmp,book)
    printf("%s %ld\n",jval_s(tmp->key),jval_l(tmp->val));
  
  printf("Ban muon tim kiem ten nao:");
  __fpurge(stdin);
  gets(name);
  __fpurge(stdin);
  tmp=jrb_find_str(book,name);
  if(tmp==NULL)
    printf("Khong co\n");
  else
    printf("%s: %ld\n",name,jval_l(tmp->val));
    
   jrb_traverse(tmp, book)
  free(jval_s(tmp->key));
  jrb_free_tree(book);
}
