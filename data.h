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

typedef struct NODE{
  int not_null;
  int pos_word;
  int num_occur;
}*node;

/* Dado um conjuto de vertices e uma palavra
 * é possível obter o número de ocorrencia dessa
 * palavra.
 * E para cada nó da tabela é possível obter a
 * palavra e o número de ocorrencia dessa
 * palavar.
 */
typedef struct WORD_TABLE{
  Vertice *set;
  node word_vert_neig;
  int length_vert_neig;
  int free_vert_neig;
  node word_neig;
  int length_neig;
  int free_neig;
  
  double f;
}*word_table;

typedef struct NEIGHBORHOOD{
  Vertice *vertice;
  int size;
  word_table table;
}Neighborhood;

struct VERTICE{
  char **info;
  char size_info;
  Neighborhood neighborhood;
};

typedef struct DATA{
  char **alphabet;
  char *first_char;
  int size_alphabet;
  double constant;
  struct Vertice_Head{
    Vertice vertice;
    int length;
    int first_free_pos;
  }vertice_head;
}Data;

void read_data(int, char**);
char **chop(char *);

#endif /* DATA_H */
