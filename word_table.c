#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

extern Data data;

typedef enum{
  VERT_NEIG,
  NEIG
}type;

static int prime[] = {
  11,
  23,
  47,
  97,
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
}, neig = 0, vert_neig = 0;

node node_init(int size){
  node aux;
  if(!(aux = calloc(size, sizeof *aux))){
    printf("Memória insuficiente\n");
    exit(0);
  }
  return aux;
}

word_table word_table_init(int size_set){
  word_table aux = malloc(sizeof *aux);
  if(!aux){
    printf("Memória insuficiente\n");
    exit(0);
  }
  aux->set = malloc(size_set * sizeof *aux->set);
  aux->word_vert_neig = node_init(aux->length_vert_neig = prime[vert_neig++]);
  aux->word_neig = node_init(aux->length_neig = prime[neig++]);
  return aux;
}

long hash(int pos, word_table table, type t){
  unsigned int h = 0;
  Vertice *c;
  for(c = table->set + t; *c; c++)
    h = (h * data.size_alphabet + ((*c)->info[pos] - data.first_char)) % table->length_neig;
  return h;
}

node neig_search(int pos, word_table table){
  long h = hash(pos, table, NEIG);
  node aux;
  Vertice *c;
  /* Percorre o bloco do linear probing */
  for(aux = &(table->word_neig[h]); (*aux).not_null; aux++){
    /* Verifica se a palavra bate com alguma palavra do bloco */
    for(c = table->set; *c && (*c)->info[(*aux).pos_word] == (*c)->info[pos]; c++)
      if(!*(c + 1))
	return aux;
  }
  return NULL;
}

void neig_insert(int pos, word_table table){
  long h = hash(pos, table, NEIG);
  while(table->word_vert_neig[h].not_null)
    h = (h + 1) % table->length_neig;
  table->word_vert_neig[h].not_null = 1;
  table->word_vert_neig[h].pos_word = pos;
  table->word_vert_neig[h].num_occur++;
}

void word_table_insert(int pos, word_table table){
  node aux;

  /* inserindo na  tabela de palavras formado pela vizinhança do vértice */
  if(!(aux = neig_search(pos, table))){
    neig_insert(pos, table);
    aux = neig_search(pos, table);
    printf("%d\n", aux->num_occur);/* <-- Erro de segentação */
  }
  else
    aux->num_occur++;
}
