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
    //printf("%c \n", n);

    //printf("%d \n", columns_found);

    if (n == '\n')
    {
      printf("%d \n", column);
      columns_found = 1;
      row++;
    }
    if (columns_found == 0)
    {
      //printf("lol");
      column++;
    }
    //printf("%c \n", n);
    //printf("%d \n", n);
    n = fgetc(infile);
  }

  printf("%d \n", column);
  printf("%d \n", row);

  rewind(infile);
  u[0].rows = row;
  u[0].columns = column;
  items = row * column;

  u[0].array = malloc(sizeof(int) * items);

  if (u[0].array == NULL)
  {
    printf("Error! memory not allocated.");
    exit(0);
  }

  n = fgetc(infile);
  //printf("ok");
  //printf("%c \n", n);

  while (n != EOF)
  {
    if (n != '\n')
    {
      for (i = 0; i < row; i++)
      {
        //printf("%d \n", column);
        for (j = 0; j < column; j++)
        {
          *(u[0].array + i * column + j) = n;

          //printf("%c \n", n);

          //printf("%d \n", *(u[0].array + i * column + j));
        }
      }
    }
    n = fgetc(infile);
  }

  for (i = 0; i < u[0].columns; i++)
  {
    printf("%c", u[0].array[i]);
    if (i == (u[0].columns - 1))
      printf("\n");
  }

  fclose(infile);

  // while ((read = getline(&line, &len, infile)) != -1)
  // {
  //   //printf("%zu\n", read);
  //   u[0].rows++;
  //   printf("%s\n", line);
  // }

  //   for (i = 0; i < read; i++)
  //     u[0].columns++;

  // if (line)
  //   free(line);

  // printf("%d %d  \n", u[0].columns, u[0].rows);

  // u[0].array = malloc(sizeof(char) * u[0].columns);
  // for (i = 0; i < u[0].columns; i++)
  // {
  //   u[0].array[i] = malloc(sizeof(char)*u[0].rows);
  // }

  // while ((read = getline(&line, &len, infile)) != -1)
  // {
  //   printf("%s\n", line);

  //   for (i = 0; i < read; i++)
  //     u[0].array[nrows][i] = line[i];
  //   nrows++;
  //   //printf("%d \n", nrows);
  //   a++;
  // }

  free(u[0].array);
  // fclose(infile);
  // if (line)
  //   free(line);
}

void write_out_file(FILE *outfile, struct universe *u)
{
  int i;

  for (i = 0; i < 20; i++)
  {
    //fwrite(u[0].array[i], sizeof(char), sizeof(u[0].array[i]), outfile);
    fwrite("\n", sizeof(char), 1, outfile);
  }
  //fwrite (u[0].array , sizeof(char), sizeof(u[0].array), outfile);
  //fclose (outfile);
}
