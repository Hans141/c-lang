#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "libfdr/fields.h"
#include "libfdr/jrb.h"

void trim(char *s)
{
  char *p = s;
  int l = strlen(p);
  while (isspace(p[l - 1]))
    p[--l] = 0;
  while (*p && isspace(*p))
    ++p, --l;
  memmove(s, p, l + 1);
}

typedef struct
{
  char *id;
  char *name;
} Product;

int main()
{
  IS in = new_inputstruct("sanpham.txt");
  if (!in)
  {
    puts("Cannot open the given file");
    exit(1);
  }
  char *word;
  int n;
  get_line(in);
  word = in->fields[0];
  // printf("%d", atoi(word));
  while (get_line(in) > 0)
  {
    printf("%d", in->line);
    // pro[in->line - 1].id = in->fields[1];
    // pro[in->line - 1].name = in->fields[0];
    
  }
  jettison_inputstruct(in);
}