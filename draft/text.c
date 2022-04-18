// #include <stdio.h>
// #include <string.h>
// #include <assert.h>
// #include <stdlib.h>
// #include "fields.h"

// // void truncate(s, k)
// // {
// //   if (s[k - 1] == '\n')
// //     s[k - 1] = '\0';
// //   if (s[k - 2] == '\r')
// //     s[k - 2] = '\0';
// // }

// void input(const char *file)
// {
//   IS in = new_inputstruct(file);
//   if (!in)
//   {
//     puts("Cannot open the given file");
//     exit(1);
//   }
//   char id[5];
//   char stop[40], prev[40];
//   int k;

//   while (get_line(in) > 0)
//   {
//     k = strlen(in->text1);
//     truncate(in->text1, k);
//     strcpy(stop, in->text1 + strlen(in->fields[0]) + 1);
//   }

//   while (get_line(in) > 0)
//   {
//     prev[0] = '\0'; // new line

//     k = strlen(in->text1);
//     truncate(in->text1, k);

//     strncpy(id, in->fields[0], 5);
//     k = strlen(id);
//     if (id[k - 1] == ':')
//       id[k - 1] = '\0';
//     jrb_insert_str(lines, strdup(id), new_jval_s(strdup(in->text1 + strlen(in->fields[0]) + 1)));

//     k = 0;
//     for (int i = 1; i < in->NF; i++)
//     {
//       if (i + 1 == in->NF)
//       {
//         strcpy(stop + k, in->fields[i]);
//         k += strlen(in->fields[i]) + 1;
//       }
//       if (in->fields[i][0] == '-' || i + 1 == in->NF)
//       {
//         stop[k - 1] = '\0';
//         k = 0;
//         if (prev[0] != '\0')
//         {
//           newLine(m, prev, stop, id);
//           newLine(m, stop, prev, id);
//         }
//         strcpy(prev, stop);
//       }
//       else
//       {
//         strcpy(stop + k, in->fields[i]);
//         k += strlen(in->fields[i]);
//         stop[k++] = ' ';
//       }
//     }
//   }

//   while (get_line(in) >= 0)
//   {
//     int v1, v2;
//     double w;
//     sscanf(in->fields[0], "%d", &v1);
//     sscanf(in->fields[1], "%d", &v2);
//     sscanf(in->fields[2], "%lf", &w);
//     // printf("%d %d\n", v1, v2);
//     addDistance(m, v1, v2, w);
//   }

//   jettison_inputstruct(in);
// }

// char s[40], d[40];
// int k;

// char _main()
// {
//   puts("1. print bus lines");
//   puts("2. print bus routes cross a station");
//   puts("3. find the shortest path");
//   puts("any key = exit");
//   printf("choice: ");
//   fgets(s, 40, stdin);
//   switch (s[0])
//   {
//   case '1':
//     printf("Line: ");
//     fgets(s, 40, stdin);
//     k = strlen(s);
//     truncate(s, k);
//     {
//       JRB n;
//       n = jrb_find_str(lines, s);
//       if (!n)
//         puts("No such line");
//       else
//         puts((n->val).s);
//     }
//     return 1;
//   case '2':
//     printf("Station name: ");
//     fgets(s, 40, stdin);
//     k = strlen(s);
//     truncate(s, k);
//     {
//       char *l;
//       char f = 0;
//       JRB n;
//       jrb_traverse(n, lines)
//       {
//         l = strstr((n->val).s, s);
//         if (l)
//         {
//           f = 1;
//           puts((n->key).s);
//         }
//       }
//       if (!f)
//         puts("No such station");
//     }
//     return 1;
//   case '3':
//     printf("Start at: ");
//     fgets(s, 40, stdin);
//     k = strlen(s);
//     truncate(s, k);

//     printf("Destination: ");
//     fgets(d, 40, stdin);
//     k = strlen(d);
//     truncate(d, k);

//     shortest_path(m, s, d);
//     return 1;
//   default:
//     return 0;
//   }
// }

// int main(int argc, char *argv[])
// {
//   if (argc != 2)
//   {
//     puts("Usage: <filename>");
//     return 1;
//   }
//   m = new_map();
//   lines = make_jrb();
//   input(argv[1]);
//   while (_main())
//   {
//     puts("==================");
//   }
//   dropMap(m);

//   jrb_traverse(n, lines)
//   {
//     if ((n->key).s)
//       free((n->key).s);
//     if ((n->val).s)
//       free((n->val).s);
//   }
//   jrb_free_tree(lines);

//   return 0;
// }