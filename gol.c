#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gol.h"

void read_in_file(FILE *infile, struct universe *u)
{
  //struct universe u;
  char *line = NULL;
  char *words[30];
  int nrows = 0;
  char n;
  int i;
  int j;
  size_t len = 0;
  size_t read;

  if (infile == NULL)
  {
    fprintf(stderr, "can't open file\n");
    exit(EXIT_FAILURE);
  }

  while ((read = getline(&line, &len, infile)) != -1)
  {
    //printf("%s \n", line);

    for (i = 0; i < 20; i++)
      u[0].array[nrows][i] = line[i];
    nrows++;
    //printf("%d \n", nrows);
  }
    for (i = 0; i < 20; i++)
    {
      printf("%c", u[0].array[6][i]);
    }
    // if (i == 18)
    // {
    printf("\n");
    // }

  fclose(infile);
  if (line)
    free(line);
}
