#include <stdio.h>
#include <stdlib.h>

#include "glob.h"

int end_read_vertice(char *line){
  while(*line == ' ')
    line++;
  if(*line)
    return 0;
  return 1;
}

void read_vertice(char *line){
  
}
