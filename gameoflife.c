#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gol.h"

void print_array(struct universe *v)
{
  int i;
  int j;

  for (i = 0; i < v->rows; i++)
  {
    for (j = 0; j < v->columns; j++)
    {
      printf("%c", v->array[(i * v->columns) + j]);
      if (j == (v->columns - 1))
        printf("\n");
    }
  }
}

int main(int argc, char *argv[])
{
  struct universe v;
  char *input_filename = (char *)NULL;
  char *output_filename = (char *)NULL;
  int number_of_generations = 5;
  int statistics = 0;
  int torus_topology = 0;
  int i;
  int j;
  int infile_supplied = 0;
  int outfile_supplied = 0;
  FILE *infile;
  //FILE *infile2;
  FILE *outfile;
  //char *standard;

  while (*++argv)
  {
    if (*argv[0] == '-' && strlen(*argv) == 2)
    {
      switch (argv[0][1])
      {
      case 'i':
        input_filename = argv[1];
        infile_supplied = 1;

        break;

      case 'o':
        output_filename = argv[1];
        outfile_supplied = 1;
        break;

      case 'g':
        number_of_generations = atoi(argv[1]);
        break;

      case 's':
        statistics = 1;
        break;

      case 't':
        torus_topology = 1;
        break;
      }
    }
  }

  if (infile_supplied == 0)
  {
    0;
    //infile = fopen(stdin, "r");
  }
  else
  {
    infile = fopen(input_filename, "r");
  }

  if (outfile_supplied == 0)
  {
    outfile = stdout;
  }
  else
  {
    outfile = fopen(output_filename, "w");
  }

  // printf("%s \n", input_filename);
  // printf("%s \n", output_filename);
  // printf("%d \n", number_of_generations);
  // printf("%d \n",print_statistics);
  // printf("%d \n", torus_topology);

  read_in_file(infile, &v);

  if (outfile == NULL)
  {
    /* File not created hence exit */
    printf("Unable to create file.\n");
    exit(EXIT_FAILURE);
  }

  v.alive = malloc(sizeof(float) * number_of_generations);
  v.generations = number_of_generations+1;
  v.evolutions = 0;

  if (statistics == 1)
  {
    
    print_statistics(&v);
  }

  printf("%d \n", number_of_generations);
  printf("%d \n", v.generations);

  for (i = 0; i < number_of_generations; i++)
  {
    evolve(&v, will_be_alive);
    if (statistics == 1)
    {
      
      print_statistics(&v);
    }
  }
    

  write_out_file(outfile, &v);
  printf("\n");
  if (statistics == 1)
  {
    printf("%.3f %% of cells currently alive\n", v.current_average);
    printf("%.3f %% of cells alive on average\n", v.average);
  }

  free(v.array);
  return 0;
}
