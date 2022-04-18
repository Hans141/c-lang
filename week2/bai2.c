#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MaxPhanTu 10
#define Max 20

typedef union
{
int i;
long l;
float f;
double d;
void *v;
char *s;
char c;
}Jval;
	
Jval new_jval_i(int i) {Jval j; j.i = i; return j;}
Jval new_jval_l(long l) { Jval j; j.l = l; return j; }
Jval new_jval_f(float f) { Jval j; j.f = f; return j; }
Jval new_jval_s(char *s) { Jval j; j.s = s; return j; }
Jval new_jval_c(char c) { Jval j; j.c = c; return j; }
Jval new_jval_d(double d) { Jval j; j.d = d; return j; }
Jval new_jval_v(void *v) { Jval j; j.v = v; return j; }

int jval_i(Jval j) { return j.i; }
long jval_l(Jval j) { return j.l; }
char* jval_s(Jval j) { return j.s; }
char jval_c(Jval j) { return j.c; }
float jval_f(Jval j) { return j.f; }
double jval_d(Jval j) { return j.d; }
void *jval_v(Jval j) { return j.v; }

Jval* create_array_i(int n)
{
  int i;
  Jval* array;
  array= (Jval *) malloc(sizeof(Jval)*n);
  for(i=0;i<n;i++)
    *(array+i) = new_jval_i(rand()%MaxPhanTu );
  return array;
}
/*
Jval *createArray(int size)
{
  Jval *a;int i;
  srand((int)time(0));
  a=(Jval*)malloc(size*sizeof(int));
  printf(".");
  for(i=0;i<size;i++)
    *(a+i)=new_jval_i(rand()%MaxPhanTu);
  return a;
}
*/
int compare_i(Jval* a, Jval* b)
{
  if(jval_i(*a)==jval_i(*b))
    return 0;
  if (jval_i(*a) < jval_i(*b)) return -1;
  else return 1;
}

void SWAP(Jval *n1,Jval *n2)
{
  Jval* temp;
  temp=(Jval*)malloc(sizeof(Jval));
  *temp=*n1;
  *n1=*n2;
  *n2=*temp;
  free(temp);
}

void sort_gen(Jval list[], int left, int right,int (*compare)(Jval* x,Jval* y))
{
  Jval* pivot;
  int i, j;
  if(left < right)
    {
      i = left;
      j = right+1;
      pivot = &list[left];
      do
	{
	  do i++; while(compare(&list[i],pivot)<0);
	  do j--; while(compare(&list[j],pivot)>0);
	  if (i < j) SWAP(&list[i],&list[j]);
	} while (i < j);
      SWAP(&list[left],&list[j]);
      sort_gen(list, left, j-1,compare);
      sort_gen(list, j+1, right,compare);
    }
}

int search_gen(Jval buf[],int l,int r,Jval item,int (*compare)(Jval* x,Jval* y))
{
  int i,res;
  if (r < l) return -1;
  i = (l + r)/2;
  res = compare(&item,&(buf[i]));
  if (res == 0)
    return i;
  else
    if(res < 0)
      return search_gen(buf,l,i-1,item,compare);
    else
      return search_gen(buf,i+1,r,item,compare);
}

int main()
{
  Jval* array;
  Jval x;
  array=create_array_i(Max);
  for(int i=0;i<Max;i++)
    printf("%d ",jval_i(array[i]));
   printf("\n");
  
  sort_gen(array,0,Max-1,compare_i);
  for(int i=0;i<Max;i++)
    printf("%d ",jval_i(array[i]));
  printf("\n");
  x.i=3;
  printf("So 3 o vi tri %d (tinh tu 0)\n",search_gen(array,0,Max-1,x,compare_i));
  
}
