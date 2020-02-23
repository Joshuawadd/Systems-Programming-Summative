#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gol.h"
int main(int argc, char *argv[])
{
  struct universe v;
  char *input_filename = (char *)NULL;
  char *output_filename = (char *)NULL;
  int number_of_generations = 0;
  int print_statistics = 0;
  int torus_topology = 0;
  int i;
  int j;
  FILE *infile;
  FILE *outfile;

  while (*++argv)
  {
    //printf("%s \n", *argv);
    if (*argv[0] == '-' && strlen(*argv) == 2)
    {
      //printf("Yes \n");
      //printf("%s \n", argv[1]);
      //printf("%c \n", argv[0][1]);
      switch (argv[0][1])
      {
      case 'i':
        //printf("%c \n", argv[0][1]);
        input_filename = argv[1];
        //printf("input \n");
        //printf("%s \n", input_filename);
        break;

      case 'o':
        //printf("%c \n", argv[0][1]);
        output_filename = argv[1];
        //printf("output \n");
        //printf("%s" "\n", output_filename);
        break;

      case 'g':
        number_of_generations = atoi(argv[1]);
        break;
      //printf(output_filename, "\n");\

      case 's':
        print_statistics = 1;
        break;

      case 't':
        torus_topology = 1;
        break;
      }
    }
  }

  infile = fopen(input_filename, "r");
  printf("%s \n", input_filename);
  printf("%s"
         "\n",
         output_filename);
  printf("%d"
         "\n",
         number_of_generations);
  printf("%d"
         "\n",
         print_statistics);
  printf("%d"
         "\n",
         torus_topology);

  read_in_file(infile, &v);

  for (i = 0; i < v.rows; i++)
  {
    for (j = 0; j < v.columns; j++)
    {
      printf("%c", v.array[(i*v.columns)+j]);
      if (j == (v.columns - 1))
        printf("\n");
    }
    
  }

  outfile = fopen(output_filename, "w");

  if (outfile == NULL)
  {
    /* File not created hence exit */
    printf("Unable to create file.\n");
    exit(EXIT_FAILURE);
  }

  // evolve(&v,will_be_alive);
  // evolve(&v,will_be_alive);
  // evolve(&v,will_be_alive);
  // evolve(&v,will_be_alive);
  // evolve(&v,will_be_alive);
  write_out_file(outfile, &v);

  free(v.array);
  return 0;
}
