#ifndef SAFE_H
#define SAFE_H

#include <stdio.h>
#include <stdlib.h>

void error(char *);
FILE *safe_fopen(char *, char *);
void *safe_malloc(size_t);
void *safe_realloc(void *, size_t);

#endif
