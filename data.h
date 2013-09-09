#ifndef DATA_H
#define DATA_H

/*
 * Como imprimir a lista de possíveis vizinhos para cada vértice:
 *  char **aux = NULL;
 *  int j = 0;
 *  int i = 0;
 *  for(i = 0; i < data.vertice_head.first_free_pos; i++){
 *    for(j = 0; j < data.vertice_head.vertice[i].neighborhood.size; j++){
 *      for(aux = data.vertice_head.vertice[i].neighborhood.vertice[j]->info; *aux; aux++)
 *            printf("%s ", *aux);
 *      printf("\n");
 *    }
 *    printf("\n");
 *  }
 */
typedef struct VERTICE *Vertice;

typedef struct NEIGHBORHOOD{
  Vertice *vertice;
  int size;
  int *word_table;
}Neighborhood;

struct VERTICE{
  char **info;
  Neighborhood neighborhood;
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
