#include "safe.h"

void error(char *str){
  perror(str);
  exit(0);
}

FILE *safe_fopen(char *name, char *mode){
  FILE *file = fopen(name, mode);
  if(!file)
    error("fopen");
  return file;
}

void *safe_malloc(size_t size){
  void *aux = malloc(size);
  if(!aux)
    error("malloc");
  return aux;
}

void *safe_realloc(void *array, size_t size){
  if(!(array = realloc(array, size)))
    error("realloc");
  return array;
}
