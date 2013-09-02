/* O alfabeto foi implementado com hashing linear probing */

#include "alphabet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prime[] = {
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

static char **alphabet = NULL;
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
int hash(char *s){
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
  while(alphabet[i] != NULL)
    i = (i + 1) % length_vector;
  alphabet[i] = character;
  vector_free_space--;
}

/* aloca espaço sempre que o vetor alcança metade das posições ocupadas */
void alloc_alphabet(){
  char **aux_alphabet = alphabet;
  int aux_length_vector = length_vector;
  int i = 0;

  /* Verificando se o alphabet precisa de espaço */
  if(vector_free_space <= length_vector / 2){

    /* alocando */
    vector_free_space = length_vector = prime[iprime++];
    if(!(alphabet = calloc(length_vector, sizeof(*alphabet))))
      memory_error();

    /* Reinserindo os símbolos no novo vetor */
    for(i = 0; i < aux_length_vector; i++)
      if(aux_alphabet[i])
	insert_alphabet(aux_alphabet[i]);
    free(aux_alphabet);
  }
}

char *search_alphabet(char *symbol){
  int i = hash(symbol);
  if(alphabet)
    while(alphabet[i] != NULL)
      if(!strcmp(symbol, alphabet[i]))
	return alphabet[i];
      else
	i = (i + 1) % length_vector;
  return NULL;
}

/* Recebe uma linha com os characters e insere os caracteres no alfabeto */
void create_alphabet(char *line){
  char *aux = NULL;
  int state = 0;
  int number_words = 0;
  int isymbol = 0;

  if(!line)
    format_error();

  /* Contando palavras */
  for(aux = line; *aux; aux++)
    switch(state){
    case 0:
      if(*aux != ' '){
	state = 1;
	number_words++;
      }
      break;
    case 1:
      if(*aux == ' ')
	state = 0;
      break;
    }

  if(!(symbol = malloc(number_words * sizeof *symbol))){
    printf("Memória insuficiente");
    exit(0);
  }

  /* Deletando espaços e guardando os simbolos no vetor de simbolos*/
  for(state = 0; *line; line++){
    switch(state){
    case 0:
      if(*line != ' '){
	state = 1;
	symbol[isymbol++] = line;
      }
      else
	*line = '\0';
      break;
    case 1:
      if(*line == ' '){
	state = 0;
	*line = '\0';
      }
      break;
    }
  }
  
  /* inserindo simbolos no alfabeto */
  for(isymbol = 0; isymbol < number_words; isymbol++){
    if(!search_alphabet(symbol[isymbol])){
      alloc_alphabet();
      insert_alphabet(symbol[isymbol]);
    }
    else
      printf("Letra %s repetiu\n", symbol[isymbol]);
  }
}

void delete_alphabet(){
  free(alphabet);
  free(symbol);
}
