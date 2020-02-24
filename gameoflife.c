#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gol.h"

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
  FILE *outfile;

  while (*++argv)
  {
    if (*argv[0] == '-' && strlen(*argv) == 2)
    {
      switch (argv[0][1])
      {
      case 'i':
        if (infile_supplied == 1)
        {
          fprintf(stderr, "Cannot supply more than one input file.\n");
          exit(EXIT_FAILURE);
        }
        input_filename = argv[1];
        infile_supplied = 1;

        break;

      case 'o':
        if (outfile_supplied == 1)
        {
          fprintf(stderr, "Cannot supply more than one output file.\n");
          exit(EXIT_FAILURE);
        }
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

  read_in_file(infile, &v);

  if (outfile == NULL)
  {
    /* File not created hence exit */
    printf("Unable to create file.\n");
    exit(EXIT_FAILURE);
  }

  v.generations = number_of_generations;
  v.evolutions = 0;
  v.alive = 0;
  v.dead = 0;

  if (statistics == 1)
  {

    print_statistics(&v);
  }

  for (i = 0; i < number_of_generations; i++)
  {
    if (torus_topology == 1)
    {
      evolve(&v, will_be_alive_torus);
    }
    else
    {
      evolve(&v, will_be_alive);
    }

    if (statistics == 1)
    {

      print_statistics(&v);
    }
  }

  write_out_file(outfile, &v);
  printf("\n");
  if (statistics == 1)
  {
    fprintf(stdout, "%.3f %% of cells currently alive\n", v.current_average);
    fprintf(stdout, "%.3f %% of cells alive on average\n", v.average);
  }

  free(v.array);
  return 0;
}
