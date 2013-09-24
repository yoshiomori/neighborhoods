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
}, neig, vert_neig;

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
  neig = 0, vert_neig = 0;
  if(!(aux->set = malloc(size_set * sizeof *aux->set))){
    printf("Memória insuficiente\n");
    exit(0);
  };
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
  long h;
  Vertice *c;
  /* Percorre o bloco do linear probing */
  for(h = vert_neig_hash(pos, table); table->word_vert_neig[h].not_null; h = (h + 1) % table->length_vert_neig){
    /* Verifica se a palavra bate com alguma palavra do bloco */
    for(c = table->set; *c && (*c)->info[table->word_vert_neig[h].pos_word] == (*c)->info[pos]; c++)
      if(!*(c + 1))
	return &table->word_vert_neig[h];
  }
  return NULL;
}

void expand_vert_neig(word_table table){
  node aux = table->word_vert_neig;
  int aux_length = table->length_vert_neig;
  int i, h;

  /* inciando uma tabela maior */
  table->word_vert_neig = node_init(table->length_vert_neig = prime[vert_neig++]);
  table->free_vert_neig = table->length_vert_neig;

  /* Reinserindo */
  for(i = 0; i < aux_length; i++)
    if(aux[i].not_null){
      h = vert_neig_hash(aux[i].pos_word, table);
      while(table->word_vert_neig[h].not_null)
	h = (h + 1) % table->length_vert_neig;
      table->word_vert_neig[h].not_null = 1;
      table->word_vert_neig[h].pos_word = aux[i].pos_word;
      table->word_vert_neig[h].num_occur = aux[i].num_occur;
      table->free_vert_neig--;
    }
  free(aux);
}

void vert_neig_insert(int pos, word_table table){
  long h = vert_neig_hash(pos, table);
  node aux;

  /* inserindo na  tabela de palavras formado pela vizinhança do vértice */
  if(!(aux = vert_neig_search(pos, table))){
    while(table->word_vert_neig[h].not_null)
      h = (h + 1) % table->length_vert_neig;
    table->word_vert_neig[h].not_null = 1;
    table->word_vert_neig[h].pos_word = pos;
    table->word_vert_neig[h].num_occur++;
    if(--table->free_vert_neig <= table->length_vert_neig / 2)
      expand_vert_neig(table);
  }
  else
    aux->num_occur++;
}

void print_vert_neig(int pos, word_table table){
  Vertice *c;
  for(c = table->set; *c; c++)
    printf("%s ", (*c)->info[pos]);
}

long neig_hash(int pos,word_table table){
  long h = 0;
  Vertice *c;
  for(c = table->set + 1; *c; c++)
    h = (h * data.size_alphabet + ((*c)->info[pos] - data.first_char)) % table->length_neig;
  return h;
}

node neig_search(int pos,word_table table){
  long h;
  Vertice *c;
  /* Percorre o bloco do linear probing */
  for(h = neig_hash(pos, table); table->word_neig[h].not_null; h = (h + 1) % table->length_neig){
    /* Verifica se a palavra bate com alguma palavra do bloco */
    for(c = table->set + 1; *c && (*c)->info[table->word_neig[h].pos_word] == (*c)->info[pos]; c++){
      if(!*(c + 1))
	return &table->word_neig[h];
    }
  }
  return NULL;
}

void expand_neig(word_table table){
  node aux = table->word_neig;
  int aux_length = table->length_neig;
  int i, h;
  /* inciando uma tabela maior */
  table->word_neig = node_init(table->length_neig = prime[neig++]);
  table->free_neig = table->length_neig;

  /* Reinserindo */
  for(i = 0; i < aux_length; i++)
    if(aux[i].not_null){
      h = neig_hash(aux[i].pos_word, table);
      while(table->word_neig[h].not_null)
	h = (h + 1) % table->length_neig;
      table->word_neig[h].not_null = 1;
      table->word_neig[h].pos_word = aux[i].pos_word;
      table->word_neig[h].num_occur = aux[i].num_occur;
      table->free_neig--;
    }
  free(aux);
}

void neig_insert(int pos, word_table table){
  long h = neig_hash(pos, table);
  node aux;

  /* inserindo na  tabela de palavras formado pela vizinhança do vértice */
  if(!(aux = neig_search(pos, table))){
    while(table->word_neig[h].not_null)
      h = (h + 1) % table->length_neig;
    table->word_neig[h].not_null = 1;
    table->word_neig[h].pos_word = pos;
    table->word_neig[h].num_occur++;
    if(--table->free_neig <= table->length_neig / 2)
      expand_neig(table);
  }
  else
    aux->num_occur++;
}

void print_neig(int pos, word_table table){
  Vertice *c;
  for(c = table->set + 1; *c; c++)
    printf("%s ", (*c)->info[pos]);
}

void print_neig_test(node n, word_table table){
  print_neig(n->pos_word, table);
  printf(":%ld, ", neig_hash(n->pos_word, table));
}

void dump_neig(void (*visit)(node, word_table), word_table table){
  node aux, stop;
  for(aux = table->word_neig, stop = aux + table->length_neig; aux < stop; aux++)
    if(aux->not_null){
      printf("pos: %ld ", aux - table->word_neig);
      visit(aux, table);
    }
}

void print_all_neig(node n, word_table table){
  print_neig(n->pos_word, table);
  printf(": %d\n", n->num_occur);
}

void dump_vert_neig(void (*visit)(node, word_table), word_table table){
  node aux, stop;
  for(aux = table->word_vert_neig, stop = aux + table->length_vert_neig; aux < stop; aux++)
    if(aux->not_null)
      visit(aux, table);
}

void print_all_vert_neig(node n, word_table table){
  node aux;
  print_vert_neig(n->pos_word, table);
  printf(" | ");
  print_neig(n->pos_word, table);
  printf(": %d / ", n->num_occur);
  aux = neig_search(n->pos_word, table);
  printf("%d\n", aux->num_occur);
}
