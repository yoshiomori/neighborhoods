#include <stdlib.h>
#include <stdio.h>
#include "data.h"

extern Data data;

static int prime[] = {
  251,
  509,
  1021,
  2039,
  4093,
  8191,
  16381,
  32749,
  65521,
  131071,
  262139,
  524287,
  1048573,
  2097143,
  4194301,
  8388593,
  16777213,
  33554393,
  67108859,
  134217689,
  268435399,
  536870909,
  1073741789,
  2147483647
};

static int hash(char **word){
  int h = 0;

  for(; *word; word++)
    printf("%s\n", *word);
    
  return h;
}

void processing(){
  int i = 0, j = 0;
  /* int subset = 0; */
  int stop = 1;
  char **word;
  Vertice *neighborhood;

  /* Calculo da vizinhança para cada vertice */
  for(i = 0; i < data.vertice_head.first_free_pos; i++){
    for(j = 0; j < data.vertice_head.vertice[i].neighborhood.size; j++)
      stop <<= 1;

    
    /* Calculo da máxima verossimilhança */
    neighborhood = &(data.vertice_head.vertice[i]);
  }
}
