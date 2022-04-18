#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dllist.h"
#include "jval.h"
#include "jrb.h"
#define SoPhanTu 9
#define goal "123456780"
#define Max 10000;

char xau[SoPhanTu]="123456078";

int TimViTriSoKhong()
{
  int i;
  for(i=0;i<SoPhanTu;i++)
    {
      if(xau[i]=='0')
	return i;
    } 
}

//int viTriSoKhong =TimViTriSoKhong();

char* sangTrai(char xauMoi[])
{
  char* a;
  a= (char*)malloc(sizeof(char)*SoPhanTu);
  strcpy(a,xauMoi);
  int i=TimViTriSoKhong();
  if(i==0||i==3||i==6)
    return NULL;
  else
    {
      a[i]=a[i-1];
      a[i-1]='0';
    }
  a[SoPhanTu]='\0';
  return a;
}

char* sangPhai(char xauMoi[])
{
  char* a;
  a= (char*)malloc(sizeof(char)*SoPhanTu);
  strcpy(a,xauMoi);
  int i=TimViTriSoKhong();
  if(i==2||i==5||i==8)
    return NULL;
  else
    {
      a[i]=a[i+1];
      a[i+1]='0';
    }
  a[SoPhanTu]='\0';
  return a;
}

char* xuongDuoi(char xauMoi[])
{
  char* a;
  a= (char*)malloc(sizeof(char)*SoPhanTu);
  strcpy(a,xauMoi);
  int i=TimViTriSoKhong();
  if(i==6||i==7||i==8)
    return NULL;
  else
    {
      a[i]=a[i+3];
      a[i+3]='0';
    }
  a[SoPhanTu]='\0';
  return a;
}

char* lenTren(char xauMoi[])
{
  char* a;
  a= (char*)malloc(sizeof(char)*SoPhanTu);
  strcpy(a,xauMoi);
  int i=TimViTriSoKhong();
  if(i==0||i==1||i==2)
    return NULL;
  else
    {
      a[i]=a[i-3];
      a[i-3]='0';
    }
  a[SoPhanTu]='\0';
  return a;
}

int kiemTraCoTrongOpen(char s[],Dllist open)
{
  Dllist node;
  dll_traverse(node,open)
    {
      if(strcmp(s,jval_s(node->val)==0))
	return 1;
    }
  return 0;
}

int kiemTraCoTrongClosed(char s[],Dllist closed)
{
  Dllist node;
  dll_traverse(node,closed)
    {
      if(strcmp(s,jval_s(node->val)==0))
	return 1;
    }
  return 0;
}

void print(char s[])
{
  for(int i=0;i<SoPhanTu;i=i+3)
    printf("%-5c%-5c%-5c\n",s[i],s[i+1],s[i+2]);
  printf("\n");
}

void ham()
{
  Dllist node;
  Dllist open = new_dllist();
  Dllist closed = new_dllist();

  char s1[SoPhanTu];
  char s2[SoPhanTu];
  char s3[SoPhanTu];
  char s4[SoPhanTu];
  char s[SoPhanTu];
  dll_append(open,new_jval_s(xau));
  while(!dll_empty(open))
    {
      node=dll_first(open);
      strcpy(s,jval_s(node->val));
      print(s);
      dll_delete_node(node);
      if(strcmp(s,goal)==0)
	{
	  printf("Success\n");
	  return;
	}
      else
	{
	  //con sang trai
	  printf("Here\n");
	  // printf("%s\n",sangTrai(s));
	  if(sangTrai(s)!=NULL)
	    {
	  strcpy(s1,sangTrai(s));
	  printf("Con sang trai: %s\n",s1);
	  if(strcmp(s1,goal)==0)
	    {
	      print(s1);
	    printf("SUCCESS\n");
	    return;
	    }
	  if(!kiemTraCoTrongClosed(s1,closed)&&!kiemTraCoTrongOpen(s1,open))
	    dll_append(open,new_jval_s(s1));
	    }

	  //con sang phai
	   if(sangPhai(s)!=NULL)
	    {
	   strcpy(s2,sangPhai(s));
	    printf("Con sang phai: %s\n",s2);
	  if(strcmp(s2,goal)==0)
	    {
	    print(s2);
	    printf("SUCCESS\n");
	    return;
	    }
	  if(!kiemTraCoTrongClosed(s2,closed)&&!kiemTraCoTrongOpen(s2,open))
	    dll_append(open,new_jval_s(s2));
	    }
	  //con len tren
	    if(lenTren(s)!=NULL)
	    {
	  strcpy(s3,lenTren(s));
	   printf("Con len tren: %s\n",s3);
	  if(strcmp(s3,goal)==0)
	    {
	    print(s3);
	    printf("SUCCESS\n");
	    return;
	    }
	    if(kiemTraCoTrongClosed(s3,closed)==0 && kiemTraCoTrongOpen(s3,open)==0)
	      {
		printf("Nah\n");
	        dll_append(open,new_jval_s(s3));
	      }
	    }
	  //con xuong duoi
	     if(xuongDuoi(s)!=NULL)
	    {
	  strcpy(s4,xuongDuoi(s));
	   printf("Con xuong duoi: %s\n",s4);
	  if(strcmp(s4,goal)==0)
	    {
	      print(s4);
	    printf("SUCCESS\n");
	    return;
	    }
	  if(!kiemTraCoTrongClosed(s4,closed)&&!kiemTraCoTrongOpen(s4,open))
	    dll_append(open,new_jval_s(s1));
	    }
	     printf("Here1\n");

	  //cho s vao closed khi da duyet xong het cac con
	  dll_append(closed,new_jval_s(s));
	  printf("Here2\n");
	}
      
    }

  printf("Khong thanh cong\n");
  free_dllist(open);
  free_dllist(closed);
}



int main()
{
  ham();
}




