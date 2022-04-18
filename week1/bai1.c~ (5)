#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Max 10000000

typedef int element;

int *createArray(int size)
{
  int *a;int i;
  srand((int)time(0));
  a=(int*)malloc(size*sizeof(int));
  for(i=0;i<size;i++)
    *(a+i)=rand()%10;
  return a;
}

int *dumpArray( int *a,int size)
{
  int *b;
  int i;
  b=(int*)malloc(size*sizeof(int));
  for(i=0;i<size;i++)
    *(b+i)=*(a+i);
  return b;
}

void exch( int a[],int i,int j)
{
  int temp;
  temp=a[i];
  a[i]=a[j];
  a[j]=temp;
}

void sort_3Way(int a[],int l,int r)
{
  if(r<=l) return;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while(1)
    {
      while(a[++i]<a[r]);
      while(a[r]<a[--j]) if(j==l) break;
      if(i>=j) break;
      exch(a,i,j);
      if(a[i]==a[r]) exch(a,++p,i);
      if(a[j]==a[r]) exch(a,--q,j);
    }
  exch(a,i,r);
  j=i-1;
  i=i+1;
  for(int k=l;k<=p;k++) exch(a,k,j--);
  for(int k=r-1;k>=q;k--) exch(a,k,i++);
  sort_3Way(a,l,j);
  sort_3Way(a,i,r);
}

void SWAP(element *a, element *b)
{
  element temp;
  temp=*a;
  *a=*b;
  *b=temp;
}

void quickSort(element list[], int left, int right)
{
  int pivot, i, j;
  if(left < right)
    {
      i = left;
      j = right+1;
      pivot = list[left];
      do
	{
	  do i++; while(list[i]< pivot);
	  do j--; while(list[j] > pivot);
	  if (i < j) SWAP(&list[i],&list[j]);
	} while (i < j);
      SWAP(&list[left],&list[j]);
      quickSort(list, left, j-1);
      quickSort(list, j+1, right);
    }
}


int main()
{
  int *a,*b;
  clock_t tstart,tfinish;
  float tcomp;
  a=createArray(Max);
  b=dumpArray(a,Max);

  tstart=clock();
  quickSort(a,0,Max-1);
  tfinish=clock();
  tcomp=(float)(tfinish-tstart)/CLOCKS_PER_SEC;
  printf("Thoi gian 2 Way chay la:%f\n",tcomp);


  tstart=clock();
  sort_3Way(b,0,Max-1);
  tfinish=clock();
  tcomp=(float)(tfinish-tstart)/CLOCKS_PER_SEC;
  printf("Thoi gian 3 Way chay la:%f\n",tcomp);
  free(a);
  free(b);
}
