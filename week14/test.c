#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgraphv1.h"
char *my_itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}
int main()
{
  /*
        int num = 2016;
        char str[20];
        if(my_itoa(num, str) != NULL)
        {
	  printf("%s %ld\n", str,strlen(str));
        }
  */
  Graph g=createGraph(UNDIRECT_GRAPH);
  addEdge(g,1,2,11);
  JRB node,node2,node3;
  node= jrb_find_int(g.edges,2);
  if(node==NULL)
    printf("NULL roi");
  else
    {
  node=(JRB) jval_v(node->val);
  node2=jrb_find_int(node,1);
  if(node==NULL)
    printf("Khong co\n");
  else
    printf("Co\n");
  printf("%f %f\n",getEdgeValue(g,1,2),getEdgeValue(g,2,1));
    }
}
