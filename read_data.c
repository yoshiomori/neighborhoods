#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "glob.h"

#define BUFFER_SIZE 1000

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
  
  return line;
}

/* Função read_data recebe os argumentos passados a na linha de comando, *
 * e lê a informação e atribui nas variáveis do programa.                */
void read_data(int argc, char **argv){
  FILE *file = NULL;

  if(argc != 2)
    info();
  else{
    if(!(file = fopen(argv[1], "r"))){
      printf("O arquivo %s não foi encontrado!\n", argv[1]);
      info();
    }

    /* Lendo o arquivo */
    while(!feof(file))
      printf("%s\n", read_line(file));
  }
}
