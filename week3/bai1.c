#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#define MaxName 80
#define MAX_PHONE_NUMBER 1000

typedef struct
{
  long number;
  char name[MaxName];
}PhoneEntry;

typedef struct
{
  PhoneEntry entries[MAX_PHONE_NUMBER];
  int total;
}PhoneBook;
/*
PhoneEntry *getPhoneEntry(char* name, const PhoneBook* book)
{
  int i;
  for(i=0;i<MAX_PHONE_NUMBER;i++)
    {
      if(strcmp(name,book->entries[i].name)==0)
	return book->entries[i];
    }
  return NULL;
}
*/
void addPhoneNumber(long number,char *name,PhoneBook* book)
{
  int i,done;
  done=0;
  for(i=0;i<book->total;i++)
    {
      if(strcmp(name,book->entries[i].name)==0)
	{
	  book->entries[i].number=number;
	  done=1;
	}
    }
  if(done==0&&book->total<MAX_PHONE_NUMBER)
    {
      book->entries[book->total].number=number;
      strcpy(book->entries[book->total].name,name);
      book->total++;
    }
  else
    if(book->total==MAX_PHONE_NUMBER)
      printf("Danh ba da day.\n");
  
}
char *getPhoneNumber(long number, PhoneBook* book)
{
  int i;
  for(i=0;i<book->total;i++)
    {
      if(number==book->entries[i].number)
	return book->entries[i].name;
    }
  return NULL;
}

int main()
{
  PhoneBook book;
  PhoneEntry entry;
  int i,n;
  printf("danh ba ban dau co so nguoi la:");
  scanf("%d",&n);
  book.total=n;
  for(i=0;i<n;i++)
    {
      printf("Nguoi thu %d\n",i+1);
      __fpurge(stdin);
      printf("Ten:");
      gets(book.entries[i].name);
      __fpurge(stdin);
      printf("SDT:");
      scanf("%ld",&book.entries[i].number);
    }
  printf("Them nguoi:\n");
  printf("Ten nguoi can them:");
  __fpurge(stdin);
  gets(entry.name);
  __fpurge(stdin);
  printf("SDT can them:");
  scanf("%ld",&entry.number);
  addPhoneNumber(entry.number,entry.name,&book);

  printf("Danh ba sau do:\n");
  for(i=0;i<book.total;i++)
    {
      printf("%s : %ld\n",book.entries[i].name,book.entries[i].number);
    }
  printf("Muon lay ten tu so:");
  scanf("%ld",&entry.number);
  if(getPhoneNumber(entry.number,&book)==NULL)
    printf("Khong co\n");
  else
    {
      strcpy(entry.name,getPhoneNumber(entry.number,&book));
      printf("Ten la:%s\n",entry.name);
    }
  
	 
}
