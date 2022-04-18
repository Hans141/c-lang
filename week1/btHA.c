#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdio_ext.h>
#include<string.h>
#define SMALL_SIZE 20
#define HUGE_SIZE 100000
typedef int element;

int *creatArray(int size){
    element *a;
    a = (element *)malloc(size*sizeof(element));
    srand((element)time(NULL));
    for(int i=0; i<size; i++){
        *(a+i) = rand()%10;
    }
    return a;
}
int *dumpArray(element *a, int size){
    element *b;
    b = (element *)malloc(size*sizeof(element));
    memcpy(b,a,size*sizeof(element));
    return b;
}

void exch(element a[], int i, int j){
    element temp;
    temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void sort_3_way(int a[],int l,int r)
{
  if(r<=l) return;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while(1)
    {
      while(a[++i]>a[r]);
      while(a[r]>a[--j]) 
      if(j==l) break;
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
  sort_3_way(a,l,j);
  sort_3_way(a,i,r);
}

int int_compare(const void *x,const void *y){
    int m = *((int *)x);
    int n = *((int *)y);
    if(m == n)
        return 0;
    else 
        return m > n ? -1 : 1;
   
}
/*int cmpfunc (const void * a, const void * b)
{
   return -( *(int*)a - *(int*)b );
}*/
void swap(element *a, element *b){
    element temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void select_sort(element a[],int size)
{
  int max;
  for(int i = 0; i < size -1; i++) {
      max = i;
      for(int j = i+1; j<size; j++){
	    if(a[j] > a[max]){
            max = j;
        }
	    swap(&a[max],&a[i]);
      }	  
    }
}

int main(){
    int *a, *b, *c;
    clock_t tstart, tfinish;
    float tcomp;
    a = creatArray(SMALL_SIZE);
    b = dumpArray(a, SMALL_SIZE);
    c = dumpArray(a, SMALL_SIZE);
    for( int i = 0; i<SMALL_SIZE; i++){
        printf(" %d", *(a + i));
    }
    printf("\n");


    tstart = clock();
    sort_3_way(a, 0, SMALL_SIZE -1);
    tfinish = clock();
    tcomp = (float)(tfinish - tstart)/CLOCKS_PER_SEC;
    printf("Thoi Gian Chay Sort_3_Way: %f", tcomp);
    printf("\n");
    for( int i = 0; i<SMALL_SIZE; i++){
        printf(" %d", *(a + i));
    }
    printf("\n");


    tstart = clock();
    qsort(b, SMALL_SIZE, sizeof(int), int_compare);
    tfinish = clock();
    tcomp = (float)(tfinish - tstart)/CLOCKS_PER_SEC;
    printf("Thoi Gian Chay Qsort: %f", tcomp);
    printf("\n");
    for( int i = 0; i<SMALL_SIZE; i++){
        printf(" %d", *(b + i));
    }
    printf("\n");


    tstart = clock();
    select_sort(c, SMALL_SIZE );
    tfinish = clock();
    tcomp = (float)(tfinish - tstart)/CLOCKS_PER_SEC;
    printf("Thoi Gian Chay Selection Sort: %f", tcomp);
    printf("\n");
    for( int i = 0; i<SMALL_SIZE; i++){
        printf(" %d", *(c + i));
    }
    printf("\n");


    return 0;
}
