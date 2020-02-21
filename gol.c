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
  int a = 0;
  int b = 0;

  if (infile == NULL)
  {
    fprintf(stderr, "can't open file\n");
    exit(EXIT_FAILURE);
  }

  while ((read = getline(&line, &len, infile)) != -1)
  {
    //printf("%zu\n", read);
    u[0].rows++;
    printf("%s\n", line);
  }
  
    for (i = 0; i < read; i++)
      u[0].columns++;

  if (line)
    free(line);

  printf("%d %d \n", u[0].columns, u[0].rows);

  u[0].array = malloc(sizeof(char) * u[0].columns);
  for (i = 0; i < u[0].columns; i++)
  {
    u[0].array[i] = malloc(sizeof(char)*u[0].rows);
  }
   

  while ((read = getline(&line, &len, infile)) != -1)
  {
    printf("%s\n", line);

    for (i = 0; i < read; i++)
      u[0].array[nrows][i] = line[i];
    nrows++;
    //printf("%d \n", nrows);
    a++;
  }

  free(u[0].array);
  fclose(infile);
  if (line)
    free(line);
}

void write_out_file(FILE *outfile, struct universe *u)
{
  int i;

  for (i = 0; i < 20; i++)
    {
      fwrite (u[0].array[i] , sizeof(char), sizeof(u[0].array[i]), outfile);
      fwrite("\n", sizeof(char), 1, outfile);
    }  
  //fwrite (u[0].array , sizeof(char), sizeof(u[0].array), outfile);
  //fclose (outfile);
}
