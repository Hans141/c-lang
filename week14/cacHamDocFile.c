//De 20192 Kip2

void docFileDang1(Graph g, char *tenFile)
{
  FILE *f;
  int id;
  char ten[Max_Str];
  f=fopen(tenFile,"r");
  if(f==NULL)
    {
      printf("File open failed!\n");
      return;
    }
  int n,m;
  fscanf(f,"%d %d\n",&n,&m);
  int i;
  for(i=0;i<n;i++)
    {
      fscanf(f,"%d %s\n",&id,ten);
      __fpurge(stdin);
      addVertex(g,id,strdup(ten));
    }
  int id1,id2;
  double trongSo;
  for(i=0;i<m;i++)
    {
      fscanf(f,"%d %d %lf\n",&id1,&id2,&trongSo);
      __fpurge(stdin);
      addEdge(g,id1,id2,trongSo);
      addEdge(g,id2,id1,trongSo);
    }
}

//De 20192 Kip1

int docFileDang2_1(char *tenFileWeb, Graph g)
{
  FILE *f;
  char ten[Max_Str];
  int ip;
  int n;
  f=fopen(tenFileWeb,"r");
  if(f==NULL)
    {
      printf("File open failed\n");
      exit(1);
    }
  fscanf(f,"%d\n",&n);
  char str[Max_Str];
  for(int i=0;i<n;i++)
    {
      fscanf(f,"%s %d\n",ten,&ip);
      strcat(ten," ");
      ten[strlen(ten)-1]=0;
      addVertex(g,ip,ten);
    }
  fclose(f);
  return n;
}

int docFileDang2_2(char *tenFile, Graph g)
{
  FILE *f;
  int ip,ipKhac;
  char str[Max_Str];
  f=fopen(tenFile,"r");
  if(f==NULL)
    {
      printf("File open failed\n");
      exit(1);
    }
  int n;
  fscanf(f,"%d\n",&n);
  for(int i=0;i<n;i++)
    {
      fscanf(f,"%d",&ip);
      fgets(str,Max_Str,f);
      str[strlen(str)-1]=0;
       strncpy(str,&str[1],strlen(str)-1);
       str[strlen(str)-1]=0;
      const char s[2] = " ";
      char *token;
      if(strlen(str)==4)
	addEdge(g,ip,atoi(str),1.0);
      else
	{
      token = strtok(str, s);
      while( token != NULL )
	{
	  printf("%s\n",token);
	  ipKhac=atoi(token);
	  printf("%d %d\n",ip,ipKhac);
	  addEdge(g,ip,ipKhac,1.0);
	  token = strtok(NULL, s);
	}
	}
    }
  fclose(f);
  return n;
}

//De 20192 kip1 dang tong quat

void docFile(char *tenFile, Graph g, int* soIP, int* soCanh. char* xauNganCach)
{

   FILE *f;
  char ten[Max_Str];
  int ip,ipKhac;
  int n;
  f=fopen(tenFileWeb,"r");
  if(f==NULL)
    {
      printf("File open failed\n");
      exit(1);
    }
  fscanf(f,"%d\n",&n);
  char str[Max_Str];
  for(int i=0;i<n;i++)
    {
      fscanf(f,"%s %d\n",ten,&ip);
      strcat(ten," ");
      ten[strlen(ten)-1]=0;
      addVertex(g,ip,ten);
    }
  *soIP=n;

  fscanf(f,"%d\n",&n);
  for(int i=0;i<n;i++)
    {
      fscanf(f,"%d",&ip);
      fgets(str,Max_Str,f);
      str[strlen(str)-1]=0;
       strncpy(str,&str[1],strlen(str)-1);
       str[strlen(str)-1]=0;
       //take note
       // new la dang ip:ip1-ip2-ip3 thi thay s[2]="-";
      const char s[2];
      strcpy(s,xauNganCach);
      //chu y ben tren
      
      char *token;
      if(strlen(str)==4)
	addEdge(g,ip,atoi(str),1.0);
      else
	{
      token = strtok(str, s);
      while( token != NULL )
	{
	  ipKhac=atoi(token);
	  addEdge(g,ip,ipKhac,1.0);
	  token = strtok(NULL, s);
	}
	}
    }
  fclose(f);
}
