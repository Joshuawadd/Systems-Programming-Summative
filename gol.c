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
  u->rows = row;
  u->columns = column;
  items = row * column;

  u->array = malloc(sizeof(char) * items);

  if (u->array == NULL)
  {
    printf("Error! memory not allocated.");
    exit(0);
  }

  n = fgetc(infile);

  while (n != EOF)
  {

    if (n != '\n')
    {

      u->array[a] = n;
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

  for (i = 0; i < u->rows; i++)
  {
    for (j = 0; j < u->columns; j++)
    {
      fprintf(outfile, "%c", u->array[(i * u->columns) + j]);
      if (j == (u->columns - 1))
        fprintf(outfile, "\n");
    }
  }
}

int is_alive(struct universe *u, int column, int row)
{
  if (u->array[(row * u->columns) + column] == '*')
  {
    return 1;
  }
  else if (u->array[(row * u->columns) + column] == '.')
  {
    return 0;
  }
}
int will_be_alive(struct universe *u, int column, int row)
{
  int i;
  int j;
  int neighbours_alive = 0;

  for (i = -1; i < 2; i++)
  {
    for (j = -1; j < 2; j++)
    {
      if (!(j == 0 && i == 0))
      {
        if (!(column + j < 0 || row + i < 0 || column + j > u->columns - 1 || row + j > u->rows - 1))
        {
          if (is_alive(u, column + j, row + i) == 1)
          {
            neighbours_alive++;
          }
        }
      }
    }
  }

  if (is_alive(u, column, row) == 1)
  {
    if (neighbours_alive == 2 || neighbours_alive == 3)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    if (neighbours_alive == 3)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
}
// int will_be_alive_torus(struct universe *u,  int column, int row)
// {

// }
void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row))
{
  int i;
  int j;
  char *array;

  array = malloc(sizeof(char) * u->columns * u->rows);

  for (i = 0; i < u->rows; i++)
  {
    for (j = 0; j < u->columns; j++)
    {
      if (rule(u, j, i) == 1)
      {
        array[(i * u->columns) + j] = '*';
      }
      else
      {
        array[(i * u->columns) + j] = '.';
      }
    }
  }

  u->array = array;
}
