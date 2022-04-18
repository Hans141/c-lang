#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libfdr/fields.h"
#include "libfdr/jrb.h"
#include "libfdr/jval.h"

void main()
{
  char name[100], id[100], nix[100];
  int count = 0;
  IS in;
  in = new_inputstruct("file.txt");
  //in = new_inputstruct(NULL); để NULL thì hiểu là lấy từ dữ liệu nhập vào(stdin) thay vì đọc từ file
  get_line(in);
  printf("%s\n", in->fields[2]);
  int k = strlen(in->text1);
  if (in->text1[k - 1] == '\n')
    in->text1[k - 1] == '\0';
  while (1)
  {
    //if (nix[count] == '=') break;
    if (in->text1[count] == '=')
      break;
    count++;
  }
  id[count] = '\0';
  strncpy(id, in->text1, count);
  //if (id[strlen(id) - 1] == '\0') id[strlen(id) - 1] == '\0';
  //if (id[strlen(id) - 2] == '\0') id[strlen(id) - 1] == '\0';
  puts(id);
  strcpy(name, in->text1 + strlen(id) + 1);
  puts(name);
  jettison_inputstruct(in);
}