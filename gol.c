#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"gol.h"

void read_in_file(FILE *infile, struct universe *u)
{
  //struct universe u;
  char line[30];
  char *words[30];
  int nrows = 0;
  int n;
  int i;
  if (infile == NULL)
  {
    fprintf(stderr, "can't open %s\n", infile);
    exit(EXIT_FAILURE);
  }

  while (fgetline(infile, line, 30) != EOF)
  {

    n = getwords(line, words, 30);

    for (i = 0; i < n; i++)
      u[0].array[nrows][i] = atoi(words[i]);
    nrows++;

    
  }

  for (i = 0; i < n; i++)
  {
    printf("%c", u[0].array[0][i]);
  }
  return 0;
}
