#include "cgraphv1.h"
#include <stdio_ext.h>
#include <stdlib.h>
#define Max_Str 100

int menuVaLuaChon(int a,int b)
{
  int luaChon,buff;
  char c;
  printf("+-----+--------------------------------------------------+\n");
  printf("|%25s%6s%25s|\n","","MENU","");
  printf("+-----+--------------------------------------------------+\n");
  printf("|%5d|%-50s|\n",1,"Y nghia");
  printf("|%5d|%-50s|\n",2,"Y nghia");
  printf("|%5d|%-50s|\n",3,"Y nghia");
  printf("|%5d|%-50s|\n",4,"Y nghia");
  printf("|%5d|%-50s|\n",5,"Y nghia");
  printf("|%5d|%-50s|\n",6,"Y nghia");
  printf("|%5d|%-50s|\n",7,"Thoat");
  printf("+-----+--------------------------------------------------+\n");

  do
    {
      __fpurge(stdin);
      printf("Nhap vao lua chon cua ban:");
      buff=scanf("%d%c",&luaChon,&c);
      if(buff!=2&&c!='\n'||luaChon<a||luaChon>b) printf("Ban da nhap sai cu phap\n");
    }while(buff!=2&&c!='\n'||luaChon<a||luaChon>b);
  return luaChon;
}

int docFileSanPham(char *tenFile, JRB caySanPham)
{
  FILE* f;
  f=fopen(tenFile,"r");
  if(f==NULL)
    {
      printf("File open failed!\n");
      exit(1);
    }
  int n;
  int id;
  char str[Max_Str];
  fscanf(f,"%d%*c",&n);
  for(int i=0;i<n;i++)
    {
      fscanf(f,"%s %d\n",str,&id);
      jrb_insert_int(caySanPham,id,new_jval_s(strdup(str)));
    }
  fclose(f);
  return n;
}

char *my_itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}

int docFileKhoHang(char *tenFile, Graph cayKhoHang, Graph g, int n)
{

   FILE* f;
  f=fopen(tenFile,"r");
  if(f==NULL)
    {
      printf("File open failed!\n");
      exit(1);
    }
  int m;
  int id;
  char str[Max_Str];
  int idSP;
  double soLuong;
  char buff[20];
  // JRB tree;
  JRB nodeTest,nodeTest2,tree2;
  fscanf(f,"%d%*c",&m);
  JRB node2,node5;
  for(int i=0;i<m;i++)
    {
      fscanf(f,"%s %d\n",str,&id);
      addVertex(g,id,str);
      for(int j=0;j<n;j++)
	{
	  fscanf(f,"%d %lf\n",&idSP,&soLuong);
	  addEdge(cayKhoHang,id,idSP,soLuong);
	}
    }
  int soCanh;
  int id1,id2;
  double khoangCach;
  fscanf(f,"%d%*c",&soCanh);
  for(int k=0;k<soCanh;k++)
    {
      fscanf(f,"%d %d %lf\n",&id1,&id2,&khoangCach);
      addEdge(g,id1,id2,khoangCach);
    }
  fclose(f);
  return m;
}

char *layTenSanPham(JRB caySanPham, int id)
{
  JRB node=jrb_find_int(caySanPham,id);
  return jval_s(node->val);
}

int main()
{
  JRB caySanPham=make_jrb();
  // JRB cayKhoHang=make_jrb();
  Graph cayKhoHang=createGraph(UNDIRECT_GRAPH);
  Graph g=createGraph(UNDIRECT_GRAPH);
  JRB node,node2,node3;
  JRB tree;
  int idKho1,idKho2;
  int thoat,luaChon;
  int i;
  int idSP,idKho,idKhoHX;
  int output[100];
  double soLuong;
  thoat=0;
  int n=docFileSanPham("sanpham.txt",caySanPham);
  int m=docFileKhoHang("khohang.txt",cayKhoHang,g,n);
  do
    {
      luaChon= menuVaLuaChon(1,7);
      switch(luaChon)
	{
	case 1:
	  //ham1
	  printf("C-Advanced,HK20182\n");
	    break;
	case 2:
	  //ham2
	  jrb_traverse(node,caySanPham)
	    printf("%s %d\n",jval_s(node->val),jval_i(node->key));
	  break;
	case 3:
	  //ham3
	  printf("Nhap vao id1:");
	  scanf("%d",&idKho1);
	  printf("Nhap vao id2:");
	  scanf("%d",&idKho2);
	  if(jrb_find_int(cayKhoHang.edges,idKho1)==NULL||jrb_find_int(cayKhoHang.edges,idKho2)==NULL)
	    {
	      printf("-1\n");
	      break;
	    }
	  if(hasEdge(g,idKho1,idKho2))
	    {
	      printf("%.5lf km\n",getEdgeValue(g,idKho1,idKho2));
	      break;
	    }
	  printf("-1\n");	    
	  break;
	case 4:
	  //ham4
	  jrb_traverse(node,g.vertices)
	    {
	      printf("%s\n",jval_s(node->val));
	      i=jval_i(node->key);
	      node2=jrb_find_int(cayKhoHang.edges,i);
	      tree=(JRB) jval_v(node2->val);
	      jrb_traverse(node2,tree)
		printf("%s %.1f\n",layTenSanPham(caySanPham,jval_i(node2->key)),jval_d(node2->val));
	      printf("\n");
	    }
	  break;
	case 5:
	  //ham5
	  printf("Nhap vao id cua san pham:");
	  scanf("%d",&idSP);
	  printf("Nhap vao id kho hang:");
	  scanf("%d",&idKho);
	  if(jrb_find_int(caySanPham,idSP)==NULL)
	    {
	      printf("Khong ton tai id san pham nay\n");
	      break;
	    }
	  if(jrb_find_int(g.vertices,idKho)==NULL)
	    {
	      printf("Khong ton tai id kho nay\n");
	      break;
	    }
	  printf("%s\n",getVertex(g,idKho));
	  node=jrb_find_int(cayKhoHang.edges,idKho);
	  node2=jrb_find_int((JRB)jval_v(node->val),idSP);
	  printf("%s %.1f\n",layTenSanPham(caySanPham,idSP),jval_d(node2->val));
	  printf("---Cac kho ke la:\n");

	  n=indegree(g,idKho,output);
	  for(i=0;i<n;i++)
	    {
	      idKhoHX=output[i];
	      printf("%s\n",getVertex(g,idKhoHX));
	  node=jrb_find_int(cayKhoHang.edges,idKhoHX);
	  node2=jrb_find_int((JRB)jval_v(node->val),idSP);
	  printf("%s %.1f\n",layTenSanPham(caySanPham,idSP),jval_d(node2->val));
	  printf("\n");
	    }
	  
	  break;
	case 6:
	  //ham6
	   printf("Nhap vao id cua san pham:");
	  scanf("%d",&idSP);
	  printf("Nhap vao so luong:");
	  scanf("%lf",&soLuong);
	  printf("Nhap vao id kho hang:");
	  scanf("%d",&idKho);
	  printf("Nhap vao id kho hang du phong:");
	  scanf("%d",&idKhoHX);
	  if(jrb_find_int(caySanPham,idSP)==NULL)
	    {
	      printf("Khong ton tai id san pham nay\n");
	      break;
	    }
	  if(jrb_find_int(g.vertices,idKho)==NULL)
	    {
	      printf("Khong ton tai id kho nay\n");
	      break;
	    }
	  if(jrb_find_int(g.vertices,idKhoHX)==NULL)
	    {
	      printf("Khong ton tai id kho du phong nay\n");
	      break;
	    }

	  node=jrb_find_int(cayKhoHang.edges,idKho);
	  node2=jrb_find_int((JRB) jval_v(node->val),idSP);
	  n=jval_d(node2->val);
	  if(n>=soLuong)
	    {
	      printf("Thanh cong, 30 phut\n");
	      break;
	    }
	  node3=jrb_find_int(cayKhoHang.edges,idKhoHX);
	  node2=jrb_find_int((JRB) jval_v(node3->val),idSP);
	  m=jval_d(node2->val);
	  // printf("%d %d\n",idKho,idKhoHX);
	  if(n+m>=soLuong)
	    {
	      printf("Thanh cong, %.1f  phut\n", 30.0+ getEdgeValue(g,idKho,idKhoHX)*2.0);
	      break;
	    }
	  printf("Mua hang that bai\n");
	  break;
	case 7:
	  thoat=1;
	  dropGraph(g);
	  free(caySanPham);
	  dropGraph(cayKhoHang);
	  break;
	}	
    }while(thoat!=1);
}
 
