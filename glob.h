#ifndef GLOB_H
#define GLOB_H

typedef struct VERTICE{
  char **vertice;
}*Vertice;

typedef struct DATA{
  char **alphabet;
  float constant;
  Vertice vertice;
}Data;

#endif /* GLOB_H */
