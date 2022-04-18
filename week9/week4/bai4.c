#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "jval.h"
#include "jrb.h"
#include <string.h>
#define MaxName 20

int main()
{
  JRB book,tmp;
  char name[MaxName];
  long sdt;
  int n;
  book=make_jrb();
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
