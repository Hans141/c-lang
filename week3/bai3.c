#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>
#define INITIAL_SIZE 3
#define INCREMENTAL_SIZE 2

typedef struct
{
  void *key;
  void *value;
}Entry;

typedef struct
{
  Entry *entries;
  int size,total;
  Entry (*makeNode)(void*, void*);
  int (*compare)(void*, void*);
}SymbolTable;

SymbolTable createSymbolTable(Entry (*makeNode)(void*, void*),int (*compare)(void*,void*))
{
  SymbolTable book;
  book.entries=(Entry*)malloc(INITIAL_SIZE*sizeof(Entry));
  book.size=INITIAL_SIZE;
  book.total=0;
  book.makeNode=makeNode;
  book.compare=compare;
  return book;
}

Entry makePhone(void *name,void* phone)
{
  Entry res;
  res.key=strdup((char*)name);
  res.value=malloc(sizeof(long));
  memcpy(res.value,phone,sizeof(long));
  return res;
}

int comparePhone(void *key1,void *key2)
{
  return strcmp((char*)key1,(char*)key2);
}


void dropPhoneBook(SymbolTable* book)
{
  free(book->entries);
}


void addEntry(void* key,void* value,SymbolTable* book)
{
  int i,done;
  done=0;
  for(i=0;i<book->total;i++)
    {
      if(book->compare(key,book->entries[i].key)==0)
	{
	  book->entries[i]=book->makeNode(key,value);
	  done=1;
	}
    }
  if(done==0&&book->total<book->size)
    {
      book->entries[book->total]=book->makeNode(key,value);
      book->total++;
    }
  else
    if(book->total==book->size)
      {
	book->entries=(Entry*)realloc(book->entries,(book->size+INCREMENTAL_SIZE)*sizeof(Entry));
	book->size=book->size+INCREMENTAL_SIZE;
	book->entries[book->total]=book->makeNode(key,value);
	book->total++;
      }
}

Entry* getEntry(void* key,SymbolTable book)
{
  int i;
  for(i=0;i<book.total;i++)
    {
      if(book.compare(key,book.entries[i].key)==0)
	return &book.entries[i];
    }
  return NULL;
}

int main()
{
  SymbolTable book;
  int i;
  Entry* entry;
  long number=972636364;
  book=createSymbolTable(makePhone,comparePhone);
  addEntry("Huy",&number,&book);
  number=12345;
  addEntry("Linh",&number,&book);
  number=33333;
  addEntry("Mai",&number,&book);
  number=12345211;
  addEntry("Hung",&number,&book);
  number=99966;
  addEntry("Dai",&number,&book);
  for(i=0;i<book.total;i++)
    printf("%s %ld\n",(char*)book.entries[i].key,(long)book.entries[i].value);
  entry=getEntry("Huy",book);
  if(entry==NULL)
    printf("Khong co\n");
   else
     printf("So dien thoai cua Huy: %ld\n",(long)entry->value);
}
