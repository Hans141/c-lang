#include <stdio.h>
#include <time.h>

void exch( int a[],int i,int j)
{
  int temp;
  temp=a[i];
  a[i]=a[j];
  a[j]=temp;
}

void sort(int a[],int l,int r)
{
  if(r<=l) return;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while(1)
    {
      while(a[++i]<a[r]);
      while(a[r]<a[--j]) if(j==i) break;
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
  sort(a,l,j);
  sort(a,i,r);
}

int main()
{
  int i;
  int a[5]={1,2,3,2,5};
  
  for(i=0;i<5;i++)
    printf("%d\n",a[i]);
  printf("\n");
  sort(a,0,4);
  for(i=0;i<5;i++)
    printf("%d\n",a[i]);
}
