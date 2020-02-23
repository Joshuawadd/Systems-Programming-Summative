#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gol.h"

void read_in_file(FILE *infile, struct universe *u)
{
  char n;
  int i;
  int j;
  int a = 0;
  int b = 0;
  int row = 0;
  int column = 0;
  int columns_found = 0;
  int items;

  if (infile == NULL)
  {
    fprintf(stderr, "can't open file\n");
    exit(EXIT_FAILURE);
  }

  n = fgetc(infile);

  while (n != EOF)
  {

    if (n == '\n')
    {
      columns_found = 1;
      row++;
    }
    if (columns_found == 0)
    {

      column++;
    }

    n = fgetc(infile);
  }

  rewind(infile);
  u[0].rows = row;
  u[0].columns = column;
  items = row * column;

  u[0].array = malloc(sizeof(char) * items);

  if (u[0].array == NULL)
  {
    printf("Error! memory not allocated.");
    exit(0);
  }

  n = fgetc(infile);

  while (n != EOF)
  {

    if (n != '\n')
    {

      u[0].array[a] = n;
      a++;
    }
    n = fgetc(infile);
  }

  fclose(infile);
}

void write_out_file(FILE *outfile, struct universe *u)
{
  int i;
  int j;

  for (i = 0; i < u[0].rows; i++)
  {
    for (j = 0; j < u[0].columns; j++)
    {
      fprintf(outfile, "%c", u[0].array[(i * u[0].columns) + j]);
      if (j == (u[0].columns - 1))
        fprintf(outfile, "\n");
    }
  }
}

int is_alive(struct universe *u, int column, int row)
{
  if (u[0].array[(row * u[0].columns) + column] == '*')
  {
    return 1;
  }
  else if (u[0].array[(row * u[0].columns) + column] == '.')
  {
    return 0;
  }
}
int will_be_alive(struct universe *u, int column, int row)
{
  int i;
  int j;
  int neighbours_alive = 0;

  for (i= -1; i<2; i++)
  {
    for (j= -1; j<2; j++)
    {
      if 
    }
  }
}
// int will_be_alive_torus(struct universe *u,  int column, int row)
// {

// }
void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row))
{

}
