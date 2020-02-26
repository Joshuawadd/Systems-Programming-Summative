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
  int items = 0;
  int column_check = 0;

  if (infile == NULL)
  {
    fprintf(stderr, "Error: Cannot open file.\n");
    exit(EXIT_FAILURE);
  }

  n = fgetc(infile);

  if (n == EOF)
  {
    fprintf(stderr, "Error: Blank file.\n");
    exit(EXIT_FAILURE);
  }

  items++;

  u->array = malloc(sizeof(char) * items);
  if (u->array == NULL)
  {
    fprintf(stderr, "Error! memory not allocated.");
    exit(EXIT_FAILURE);
  }

  while (n != EOF)
  {

    if (!(n == '.' || n == '*' || n == '\n'))
    {
      fprintf(stderr, "Error: Characters other than '*' or '.' detected.\n");
      exit(EXIT_FAILURE);
    }
    if (n == '\n')
    {

      if (columns_found == 1)
      {
        if (column == column_check)
        {
          row++;
          column_check = 0;
        }
        else
        {
          fprintf(stderr, "Invalid file: Every row does not have the same number of columns.\n");
          exit(EXIT_FAILURE);
        }
      }
      else
      {
        columns_found = 1;
        row++;
      }
    }
    else
    {
      u->array = realloc(u->array, sizeof(char) * items);
      u->array[a] = n;
      a++;
      items++;
      if (columns_found == 0)
      {
        column++;
      }
      else
      {
        column_check++;
      }
    }

    n = fgetc(infile);

    if (column > 512)
    {
      fprintf(stderr, "Invalid file: Too many columns\n");
      exit(EXIT_FAILURE);
    }
  }


  //printf("\n");
  u->rows = row;
  u->columns = column;

  // u->array = malloc(sizeof(char) * items);

  // if (u->array == NULL)
  // {
  //   fprintf(stderr, "Error! memory not allocated.");
  //   exit(EXIT_FAILURE);
  // }

  // n = fgetc(infile);

  // while (n != EOF)
  // {
  //   if (n != '\n')
  //   {
  //     u->array[a] = n;
  //     //printf("%c",n);
  //     a++;
  //   }
  //   //printf("\n");
  //   n = fgetc(infile);
  // }

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
        if (!(column + j < 0 || row + i < 0 || column + j > u->columns - 1 || row + i > u->rows - 1))
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
int will_be_alive_torus(struct universe *u, int column, int row)
{
  int i;
  int j;
  int neighbours_alive = 0;
  int torus_column = column;
  int torus_row = row;

  for (i = -1; i < 2; i++)
  {
    for (j = -1; j < 2; j++)
    {
      torus_column = column;
      torus_row = row;
      if (!(j == 0 && i == 0))
      {
        if (column + j < 0)
        {
          torus_column = column + (u->columns - 1);
        }
        if (row + i < 0)
        {
          torus_row = row + (u->rows - 1);
        }
        if (column + j > u->columns - 1)
        {
          torus_column = column - (u->columns - 1);
        }
        if (row + i > u->rows - 1)
        {
          torus_row = row - (u->rows - 1);
        }
        if (torus_column == column)
        {
          torus_column = torus_column + j;
        }
        if (torus_row == row)
        {
          torus_row = torus_row + i;
        }
        if (is_alive(u, torus_column, torus_row) == 1)
        {
          neighbours_alive++;
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

void print_statistics(struct universe *u)
{
  int i;
  int j;
  float dead = 0;
  float alive = 0;
  float average;
  float overall_average = 0;

  for (i = 0; i < u->rows; i++)
  {
    for (j = 0; j < u->columns; j++)
    {
      if (u->array[(i * u->columns) + j] == '*')
      {
        alive++;
      }
      else
      {
        dead++;
      }
    }
  }

  average = alive / (alive + dead);
  u->alive = u->alive + alive;
  u->dead = u->dead + dead;
  if (u->evolutions == u->generations)
  {
    u->average = u->alive / (u->alive + u->dead);
    u->current_average = average;
  }
  else
  {
    u->evolutions++;
  }
}
