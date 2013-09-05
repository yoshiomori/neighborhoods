#ifndef DATA_H
#define DATA_H

/* Como imprimir a lista de possíveis vizinhos para cada vértice:  *
 *  char **aux = NULL;                                             *
 *  Vertice *v = NULL;                                             *
 *  int i = 0;                                                     *
 *  for(i = 0; i < data.vertice_head.first_free_pos; i++){         *
 *    for(v = data.vertice_head.vertice[i].neighborhood; *v; v++){ *
 *      for(aux = (*v)->info; *aux; aux++)                         *
 *            printf("%s ", *aux);                                 *
 *      printf("\n");                                              *
 *    }                                                            *
 *    printf("\n");                                                *
 *  }                                                              */

typedef struct VERTICE *Vertice;
struct VERTICE{
  char **info;
  Vertice *neighborhood;
};

typedef struct DATA{
  char **alphabet;
  float constant;
  struct Vertice_Head{
    Vertice vertice;
    int length;
    int first_free_pos;
  }vertice_head;
}Data;

void read_data(int, char**);
char **chop(char *);

#endif /* DATA_H */
