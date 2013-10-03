/* O alfabeto foi implementado com hashing linear probing */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "alphabet.h"
#include "data.h"

extern Data data;

static int prime[] = {
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
};

static char **symbol = NULL;

static int length_vector = 0, iprime = 0, vector_free_space = 0;

void format_error(){
  printf("Arquivo não está no formato correto, veja arquivo_padrão\n");
  exit(0);
}

void memory_error(){
  printf("Memória insuficiente!\n");
  exit(0);
}

/* Função hash para string */
static int hash(char *s){
  int h = 0;
  
  /* O valor 254 abaixo é a quantidade de caracteres no ascii sem *
   * o espaço e o cerquilha.                                      */
  if(length_vector)
    for(h = 0; *s; s++)
      h = (254 * h + *s) % length_vector;
  return h;
}

/* insere o símbolo no alfabeto */
void insert_alphabet(char *character){
  int i = hash(character);
  while(data.alphabet[i] != NULL)
    i = (i + 1) % length_vector;
  data.alphabet[i] = character;
  vector_free_space--;
  data.size_alphabet++;
}

/* aloca espaço sempre que o vetor alcança metade das posições ocupadas */
void alloc_alphabet(){
  char **aux_alphabet = data.alphabet;
  int aux_length_vector = length_vector;
  int i = 0;

  /* Verificando se o alphabet precisa de espaço */
  if(vector_free_space <= length_vector / 2){

    /* alocando */
    vector_free_space = length_vector = prime[iprime++];
    if(!(data.alphabet = calloc(length_vector, sizeof(*data.alphabet))))
      memory_error();

    /* Reinserindo os símbolos no novo vetor */
    for(i = 0; i < aux_length_vector; i++)
      if(aux_alphabet[i])
	insert_alphabet(aux_alphabet[i]);
    if(aux_alphabet)
      free(aux_alphabet);
  }
}

char *search_alphabet(char *symbol){
  int i = hash(symbol);
  if(data.alphabet)
    while(data.alphabet[i] != NULL){
      if(!strcmp(symbol, data.alphabet[i]))
	return data.alphabet[i];
      else
	i = (i + 1) % length_vector;
    }
  return NULL;
}

/* Recebe uma linha com os characters e insere os caracteres no alfabeto */
void read_alphabet(char *line){
  char **aux = NULL;

  data.alphabet = NULL;
  data.size_alphabet = 0;

  if(!line)
    format_error();

  symbol = chop(line);
  data.first_char = *symbol;
  
  /* inserindo simbolos no alfabeto */
  for(aux = symbol; *aux; aux++){
    if(!search_alphabet(*aux)){
      alloc_alphabet();
      insert_alphabet(*aux);
    }
    else
      printf("Letra %s repetiu no alfabeto.\n", *aux);
  }
}

void delete_alphabet(){
  if(data.alphabet)
    free(data.alphabet);
  if(symbol)
    free(symbol);
}
