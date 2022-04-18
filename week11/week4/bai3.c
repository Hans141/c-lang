#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "jval.h"

int main()
{
  JRB t, tmp;// t la con tro, tro toi nut goc cua cay​
  int i, so_nguyen = 0;
  unsigned int so_luong = 0;
  t = make_jrb();//Khoi tao cay​
  printf("Ban muon nhap bao nhieu so:");
  scanf("%d",&so_luong);
  for(i = 0; i < so_luong;i++)
    {
    printf("nhap 1 so nguyen: ");
    scanf("%d",&so_nguyen);
    jrb_insert_int(t, so_nguyen, new_jval_i(so_nguyen));
    }
  printf("Day so nhap vao da duoc sap xep:\n");

  jrb_traverse(tmp, t)
    {
    printf("%2d\n", tmp->val.i);
    }
  jrb_free_tree(t);
  exit(0);

}
