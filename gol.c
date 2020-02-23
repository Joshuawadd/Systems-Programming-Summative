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
  int column_check = 0;

  if (infile == NULL)
  {
    fprintf(stderr, "can't open file\n");
    exit(EXIT_FAILURE);
  }

  //printf("lol");

  n = fgetc(infile);

  //printf("%c", n);

  while (n != EOF)
  {
    //printf("%c \n", n);

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
    else if (columns_found == 0)
    {
      column++;
    }
    else
    {
      column_check++;
    }

    n = fgetc(infile);

    if (column > 512)
    {
      fprintf(stderr, "Invalid file: Too many columns\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("%d \n", row);
  printf("%d \n", column);


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
    if (n == '\n')
      {
        printf("yay \n");
      }

    if (n != '\n')
    {
      if (n == '\n')
      {
        printf("yay");
      }
      printf("%c %d \n", n, a);
      u->array[a] = n;
      a++;
    }
    n = fgetc(infile);
    printf("%d %d \n", n, a);
    if (n == '\n')
      {
        printf("yay \n");
      }
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
  //free(u->array);
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
        //printf("%c \n", u->array[(i * u->columns) + j]);
        dead++;
      }
    }
  }
  printf("%f \n", alive);
  printf("%f \n", dead);

  average = alive / (alive + dead);
  u->alive[u->evolutions] = average;
  if (u->evolutions == u->generations)
  {
    for (i = 0; i < u->generations; i++)
    {
      overall_average = overall_average + u->alive[i];
    }
    u->average = overall_average / u->generations;
    u->current_average = average;
  }
  else
  {
    u->evolutions++;
    printf("%d \n", u->evolutions);
  }

  printf("%.3f\n", average);
}
