#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "alphabet.h"
#include "constant.h"
#include "vertice.h"

extern Data data;

#define BUFFER_SIZE 1000

int end_read_block(char *line){
  if(line){
    while(*line == ' ')
      line++;
    if(*line)
      return 0;
  }
  return 1;
}

/* Exemplo de entrada e saida da função chop:                     *
 * line = {"abc def ghi'\0'"}                                     *
 * return = {{"abc"}, {"def"}, {"ghi"}, NULL}                     */
char **chop(char *line){
  char **line_chopped = NULL;
  char *aux = NULL;
  int state = 0;
  int number_words = 0;
  int iline_chopped = 0;

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

  if(!(line_chopped = calloc(number_words + 1, sizeof *line_chopped))){
    printf("Memória insuficiente");
    exit(0);
  }

  /* Deletando espaços e guardando os simbolos no vetor de simbolos*/
  for(state = 0; *line; line++){
    switch(state){
    case 0:
      if(*line != ' '){
	state = 1;
	line_chopped[iline_chopped++] = line;
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
  return line_chopped;
}

void info(){
  printf("USO:\n\t./neighborhood NOME_DO_ARQUIVO_DE_DADOS\n\n");
  exit(0);
}

/* Apenas lê uma linha do arquivo */
char *read_line(FILE *file){
  /* alocando uma linha vazia, esse caractere allocado é o fim da string */
  char *line = malloc(sizeof(*line));
  int size_of_line = 1;
  char buffer[BUFFER_SIZE];

  int is_line_over = 0;
  int read_chars = 0;

  line[0] = '\0';

  do{
    read_chars = 0;
    fgets(buffer, BUFFER_SIZE, file);
    read_chars = strlen(buffer);

    /* Para ao encontrar um \n ou eof. Além disso se for encontrado \n, o \n será ignorado. */
    if(buffer[read_chars - 1] == '\n'){
      is_line_over = 1;
      read_chars--;
      buffer[read_chars] = '\0';
    } else if (feof(file)) {
      is_line_over = 1;
    }
    
    /* Realloca a linha para o que foi lido */
    line = realloc(line, (size_of_line + read_chars) * sizeof(*line));
    strcat(line, buffer);
    size_of_line += read_chars;

  } while(!is_line_over);

  if(line[0] == '#'){
    free(line);
    line = NULL;
  }

  while(!line && !feof(file))
    line = read_line(file);
  
  return line;
}

/* Função read_data recebe os argumentos passados a na linha de comando, *
 * e lê a informação e atribui nas variáveis do programa.                */
void read_data(int argc, char **argv){
  FILE *file = NULL;
  char *line = NULL;
  /*teste char *line = NULL;*/

  if(argc != 2)
    info();
  else{
    if(!(file = fopen(argv[1], "r"))){
      printf("O arquivo %s não foi encontrado!\n", argv[1]);
      info();
    }

    /* Lendo o arquivo */
    read_alphabet(read_line(file));
    read_line(file);
    read_constant(read_line(file));
    read_line(file);
    while(!end_read_block((line = read_line(file))))
      read_vertice(line);
    while(!end_read_block((line = read_line(file))))
      read_neighborhood(line);
  }
}