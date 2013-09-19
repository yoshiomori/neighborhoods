#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "alphabet.h"

extern Data data;

void format_error_vertice(char *symbol){
  printf("A letra %s não está presente no alfabeto!\n", symbol);
  exit(0);
}

void read_vertice(char *line){
  char **info_vertice = NULL;
  char **aux = NULL;
  unsigned long int size = 0;
  static int first_time = 1;
  static unsigned long int size_info_vertice = 0;
  static int count = 0;
  
  /* Verificando erro de sintaxe e enumerando letras da info_vertice*/
  info_vertice = chop(line);
  for(aux = info_vertice; *aux; aux++){
    if(!(*aux = search_alphabet(*aux)))/* <- enumerando */
      format_error_vertice(*aux);
    if(first_time)
      size_info_vertice++;
    size++;
  }
  if(size_info_vertice != size){
    printf("Vertice com mais informação que outras!\n");
    exit(0);
  }
  free(line);

  /* Alocando */
  if(first_time){
    if(!(data.vertice_head.vertice = malloc(10 * sizeof *data.vertice_head.vertice))){
      printf("Memória insuficiente!\n");
      exit(0);
    }
    data.vertice_head.length = 10;
    data.vertice_head.first_free_pos = 0;
  }
  else if(data.vertice_head.first_free_pos == data.vertice_head.length){
    data.vertice_head.length += data.vertice_head.length;
    if(!(data.vertice_head.vertice = realloc(data.vertice_head.vertice, data.vertice_head.length * sizeof *data.vertice_head.vertice))){
      printf("Memória insuficiente\n");
      exit(0);
    }
  }

  /* inserindo informação */
  data.vertice_head.vertice[data.vertice_head.first_free_pos].line = count++;
  data.vertice_head.vertice[data.vertice_head.first_free_pos].info = info_vertice;
  data.vertice_head.vertice[data.vertice_head.first_free_pos++].size_info = size_info_vertice;

  first_time = 0;
}

void read_neighborhood(char *line){
  char **neighborhood = NULL;
  char **aux = NULL;
  int size = 0;
  static int current_vertice = 0;
  Vertice *current_neighborhood = NULL;

  neighborhood = chop(line);

  for(aux = neighborhood, size = 0; *aux; aux++, size++)
    if((int)strlen(*aux) != 1 || (**aux != '0' && **aux != '1')){
      printf("Erro de sintaxe na matriz de vizinhança!\n");
      printf("Permitido apenas 0 ou 1 na matriz.\n");
      exit(0);
    }
  if(size != data.vertice_head.first_free_pos){
    printf("Erro de sintaxe na matriz de vizinhança!\n");
    printf("Indicação de vizinhaça a mais.\n");
    exit(0);
  }

  for(aux = neighborhood, size = 0; *aux; aux++)
    if(**aux - '0'){
      if(current_vertice == (int)(aux - neighborhood)){
	printf("Erro de sintaxe na matriz de vizinhança!\n");
	printf("Diagonal deve ser zerada.\n");
	exit(0);
      }

      /* contando quantidade de possíveis vizinhos */
      size++;
    }

  /* Alocando */
  if(!(current_neighborhood = malloc(size * sizeof *current_neighborhood))){
    printf("Memória insuficiente!\n");
    exit(0);
  }
  data.vertice_head.vertice[current_vertice].neighborhood.vertice = current_neighborhood;
  data.vertice_head.vertice[current_vertice].neighborhood.size = size;
  
  /* Inserindo neighborhood */
  for(aux = neighborhood; *aux; aux++)
    if(**aux - '0')
      *(current_neighborhood++) = &data.vertice_head.vertice[(int)(aux - neighborhood)];

  current_vertice++;
}
