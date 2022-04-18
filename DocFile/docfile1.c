#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define FILENAME "program.txt"

struct cauhoi
{
  int nhom;           // Nhóm/chương mà câu hỏi này thuộc về
  char noidung[255];  // Nội dung câu hỏi
  char dapan[5][255]; //Các đáp án khác của câu hỏi.
};
struct cauhoi arr[100];
int nhom[100];

int main(void)
{
  FILE *filePointer;
  int bufferLength = 255;
  char buffer[bufferLength];
  filePointer = fopen(FILENAME, "r");
  int soCauHoi = 0;
  int dapAnThu = 0;
  int soLuongNhom = 0;
  while (fgets(buffer, bufferLength, filePointer))
  {
    if (buffer[0] == '*')
    {
      if (!nhom[(int)buffer[2]])
      {
        soLuongNhom++;
        nhom[(int)buffer[2]] = 1;
      }
      dapAnThu = 0;
      soCauHoi += 1;
      arr[soCauHoi].nhom = (buffer[2] - '0');
      strncpy(arr[soCauHoi].noidung, buffer + 3, strlen(buffer));
    }
    else
    {
      dapAnThu++;
      strncpy(arr[soCauHoi].dapan[dapAnThu], buffer + 1, strlen(buffer));
    }
  }

  printf("so nhom: %d\n", soLuongNhom);
  // for (int i = 1; i <= soCauHoi; i++)
  // {
  //   printf("%s\n", arr[i].noidung);
  //   for (int j = 1; j < 5; j++)
  //   {
  //     printf("%s\n", arr[i].dapan[j]);
  //   }
  // }

  for (int i = 1; i <= soCauHoi; i++)
  {
    for (int j = 1; j <= i; j++)
    {
      if (arr[j - 1].nhom > arr[j].nhom)
      {
        struct cauhoi tmp = arr[j - 1];
        arr[j - 1] = arr[j];
        arr[j] = tmp;
      }
    }
  }

  for (int i = 1; i <= soCauHoi; i++)
  {
    printf("nhom: %d %s\n", arr[i].nhom, arr[i].noidung);
    for (int j = 1; j < 5; j++)
    {
      printf("%s\n", arr[i].dapan[j]);
    }
  }
  fclose(filePointer);
}
