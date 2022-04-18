#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define Max 15

int *createArray(int size)
{
  int *a;int i;
  srand((int)time(0));
  a=(int*)malloc(size*sizeof(int));
  for(i=0;i<size;i++)
    *(a+i)=rand()%10;
  return a;
}

float *createArrayFloat(int size)
{
  float *a;int i;
  srand((int)time(0));
  a=(float*)malloc(size*sizeof(float));
  for(i=0;i<size;i++)
    *(a+i)=(float)(rand()%10);
  return a;
}


int int_compare(void const* x,void const *y)
{
  int m,n;
  m=*((int*)x);
  n=*((int*)y);
  if(m==n) return 0;
  return m>n ? 1: -1;
}
/*
void sapXep(void* buf,int n,int sizePhanTu,int (*int_compare)( void const*x, void const *y))
{
  int i,j;
  void next;
  for(i=1;i<n;i++)
    {
      next =*(buf+i*sizePhanTu);
      for(j=i-1;j>=0&&(int_compare(next,*(buf+j*sizePhanTu))<1);j--)
	*(buf+j+1)=*(buf+j);
      *(buf+j+1)=next;
    }
}
void SWAP_int(int *a,int *b)
{
  int temp;
  temp=*a;
  *a=*b;
  *b=temp;
}

void *mempcy(void *region1,const void *region2,size_t n)
{
	const char* first=(const char*) region2;
	const char* last=((const char *)region2)+n;
	char *result=(char *)region1;
	while(first!=last) *result++=*first++;
	return result;
}
*/
void SWAP(void *n1,void *n2,int size)
{
	void *temp=(void *)malloc(size);
	memcpy(temp,n1,size);
	memcpy(n1,n2,size);
	memcpy(n2,temp,size);
	free(temp);
}

int float_compare(void const* x,void const *y)
{
  int m,n;
  m=*((float*)x);
  n=*((float*)y);
  if(m==n) return 0;
  return m>n ? 1: -1;
}
void quickSort(void* list, int left, int right,int sizePhanTu,int (*int_compare)( void const*x, void const *y))
{
  void* pivot;
  int i, j;
  if(left < right)
    {
      i = left;
      j = right+1;
      pivot = list+left*sizePhanTu;
      do
	{
	  do i++; while(int_compare(list+i*sizePhanTu,pivot)<0);
	  do j--; while(int_compare(list+j*sizePhanTu,pivot)>0);
	  if (i < j) SWAP(list+i*sizePhanTu,list+j*sizePhanTu,sizePhanTu);
	} while (i < j);
      SWAP(list+left*sizePhanTu,list+j*sizePhanTu,sizePhanTu);
      quickSort(list, left, j-1,sizePhanTu,int_compare);
      quickSort(list, j+1, right,sizePhanTu,int_compare);
    }
}

int main()
{
  int *a;
  float *b;
  int i;
  a=createArray(Max);
  b=createArrayFloat(Max);
  for(i=0;i<Max;i++)
    printf("%d ",a[i]);
  quickSort(a,0,Max-1,sizeof(int),int_compare);
  printf("\n");
  for(i=0;i<Max;i++)
    printf("%d ",a[i]);
  printf("\n");

  for(i=0;i<Max;i++)
    printf("%.1f ",b[i]);
  //printf(".");
  quickSort(b,0,Max-1,sizeof(float),float_compare);
  printf("\n");
  for(i=0;i<Max;i++)
    printf("%.1f ",b[i]);
  printf("\n");
}
