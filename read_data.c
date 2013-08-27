#include <stdio.h>
#include <stdlib.h>
#include "glob.h"

#define BUFFER_SIZE 1000

void info(){
  printf("USO:\n\t./neighborhood NOME_DO_ARQUIVO_DE_DADOS CONSTANTE\n\n");
  exit(0);
}

/* Apenas lê uma linha do arquivo */
char *read_line(FILE *file){
  char *line = malloc(sizeof(*line));
  int size_of_line = 1;
  
  return line;
}

/* Função read_data recebe os argumentos passados a na linha de comando, *
 * e lê a informação e atribui nas variáveis do programa.                */
void read_data(int argc, char **argv){
  FILE *file = NULL;

  if(argc != 3)
    info();
  else{
    if(!(file = fopen(argv[1], "r"))){
      printf("O arquivo %s não foi encontrado!\n", argv[1]);
      info();
    }

    /* Lendo o arquivo */
    read_line(file);
    
    /* atribuindo o valor da constante */
    c = atof(argv[2]);
  }
}
