#include <stdlib.h>
#include <stdio.h>
#define FILENAME "program.txt"

int main(void)
{
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  int line_count = 0;
  ssize_t line_size;
  FILE *fp = fopen(FILENAME, "r");
  if (!fp)
  {
    fprintf(stderr, "Lỗi đọc file '%s'\n", FILENAME);
    return EXIT_FAILURE;
  }

  /* Đọc dòng đầu tiên trong file */
  line_size = getline(&line_buf, &line_buf_size, fp);

  /* Lặp lại việc đọc và hiển thị nội dung cho tới khi hoàn tất */
  while (line_size >= 0)
  {
    /* Tăng số lượng dòng 1 đơn vị */
    line_count++;

    /* Hiển thị: 1. thứ tự của dòng, 2. số lượng ký tự trong dòng, 3. dung lượng dữ liệu và 4.nội dung cùa dòng */
    printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s", line_count, line_size, line_buf_size, line_buf);

    /* Đọc dòng tiếp theo */
    line_size = getline(&line_buf, &line_buf_size, fp);
  }
  /* Giải phóng buffer */
  free(line_buf);
  line_buf = NULL;

  /* Đóng file pointer */
  fclose(fp);

  return EXIT_SUCCESS;
}