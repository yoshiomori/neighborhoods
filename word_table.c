#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

extern Data data;

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
  aux->free_vert_neig = aux->length_vert_neig;
  aux->word_neig = node_init(aux->length_neig = prime[neig++]);
  aux->free_neig = aux->length_neig;
  aux->f = 0;
  return aux;
}

long vert_neig_hash(int pos, word_table table){
  unsigned int h = 0;
  Vertice *c;
  for(c = table->set; *c; c++)
    h = (h * data.size_alphabet + ((*c)->info[pos] - data.first_char)) % table->length_vert_neig;
  return h;
}

node vert_neig_search(int pos, word_table table){
  long h = vert_neig_hash(pos, table);
  node aux;
  Vertice *c;
  /* Percorre o bloco do linear probing */
  for(aux = &(table->word_vert_neig[h]); aux->not_null; aux++){
    /* Verifica se a palavra bate com alguma palavra do bloco */
    for(c = table->set; *c && (*c)->info[(*aux).pos_word] == (*c)->info[pos]; c++)
      if(!*(c + 1))
	return aux;
  }
  return NULL;
}

void vert_neig_insert(int, word_table);

void expand_vert_neig(word_table table){
  node aux = table->word_vert_neig;
  int aux_length = table->length_vert_neig;
  int i, h;
  printf("ok\n");

  /* inciando uma tabela maior */
  table->word_vert_neig = node_init(table->length_vert_neig = prime[vert_neig++]);
  table->free_vert_neig = table->length_vert_neig;

  /* Reinserindo */
  for(i = 0; i < aux_length; i++)
    if(aux[i].not_null){
      h = vert_neig_hash(aux[i].pos_word, table);
      table->word_vert_neig[h].not_null = 1;
      table->word_vert_neig[h].pos_word = aux[i].pos_word;
      table->word_vert_neig[h].num_occur = aux[i].num_occur;
      table->free_vert_neig--;
    }
  free(aux);
  printf("ok\n");
}

void vert_neig_insert(int pos, word_table table){
  long h = vert_neig_hash(pos, table);
  while(table->word_vert_neig[h].not_null)
    h = (h + 1) % table->length_vert_neig;
  table->word_vert_neig[h].not_null = 1;
  table->word_vert_neig[h].pos_word = pos;
  table->word_vert_neig[h].num_occur++;
  if(--table->free_vert_neig <= table->length_vert_neig / 2)
    expand_vert_neig(table);
}

void print_vert_neig(int pos, word_table table){
  Vertice *c;
  for(c = table->set; *c; c++)
    printf("%s ", (*c)->info[pos]);
}

void word_table_insert(int pos, word_table table){
  node aux;

  /* inserindo na  tabela de palavras formado pela vizinhança do vértice */
  if(!(aux = vert_neig_search(pos, table)))
    vert_neig_insert(pos, table);
  else
    aux->num_occur++;
}

double likelihood(word_table table){
  int i;
  for(i = 0; i < table->length_vert_neig; i++){
    if(table->word_vert_neig[i].not_null){
    }
  }
  return 0;
}
