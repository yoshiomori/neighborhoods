#include "alphabet.h"
#include <stdio.h>
#include <stdlib.h>

#define null(A) (alphabet[A] == NULL)

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

static int length_vector = 0, iprime = 0, vector_free_space = 0;

void format_error(){
  printf("Arquivo não está no formato correto, veja arquivo_padrão\n");
  exit(0);
}

void memory_error(){
  printf("Memória insuficiente!\n");
  exit(0);
}

int hash(char **s){
  int h = 0;
  int size_ascii_less_space_and_sharp = 254;
  for(h = 0; **s && **s != ' '; (*s)++)
    h = (size_ascii_less_space_and_sharp * h + **s) % length_vector;
  return h;
}

void alloc_alphabet(){
  int i = 0;
  /* Verificando se o alphabet precisa de espaço */
  if(alphabet){
    /* Realocando espaço */
    if(vector_free_space <= length_vector / 2){
      i = length_vector;
      length_vector = prime[iprime++];
      vector_free_space = length_vector - vector_free_space;
      if(!(alphabet = realloc(alphabet, length_vector * sizeof(*alphabet))))
	memory_error();
      for(; i < length_vector; i++)
	alphabet[i] = NULL;
    }
  }
  else{
    /* Alocando espaço */
    vector_free_space = length_vector = prime[iprime++];
    if(!(alphabet = malloc(length_vector * sizeof(*alphabet))))
      memory_error();
    for(i = 0; i < length_vector; i++)
      alphabet[i] = NULL;
  }
}

char *search_alphabet(char *character){
  return NULL;
}

void insert_symbol(char **character){
  char *c = *character;
  int i = hash(character);
  while(!null(i))
    i = (i + 1) % length_vector;
  alphabet[i] = c;
  vector_free_space--;
}

/* pula os espaços */
void jump_spaces(char **character){
  while(**character && **character == ' '){
    **character = '\0';
    (*character)++;
  }
}

void insert_alphabet(char *character){
  if(!character)
    format_error();

  while(*character){
    jump_spaces(&character);
    
    /* inserindo simbolos no alfabeto */
    alloc_alphabet();
    insert_symbol(&character);
  }
  for(; length_vector; length_vector--, alphabet++)
    if(*alphabet)
      printf("%s\n", *alphabet);
}
