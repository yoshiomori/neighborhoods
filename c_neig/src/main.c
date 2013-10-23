#include <ctype.h>
#include <string.h>
#include "safe.h"

int main(int argc, char **argv){
  FILE *file = safe_fopen(argv[1], "r+");
  char c;
  int **mat = safe_malloc(10 * sizeof *mat);
  int mat_i = 0, mat_len = 10;
  int *lin = safe_malloc(10 * sizeof *lin);
  int lin_i = 0, lin_len = 10;
  
  if(argc != 3){
    printf("Erro de argumentos\n");
    printf("Uso: %s <nome_do_arquivo_de_entrada> <nome_do_arquivo_gerado> <0 ou 1>\n", argv[0]);
    exit(0);
  }
  else if(strlen(argv[2]) != 1){
    printf("Erro de argumentos\n");
    printf("Uso: %s <nome_do_arquivo_de_entrada> <nome_do_arquivo_gerado> <0 ou 1>\n", argv[0]);
    exit(0);
  }
  else if(argv[2][0] != '0' && argv[2][0] != '1'){
    printf("Erro de argumentos\n");
    printf("Uso: %s <nome_do_arquivo_de_entrada> <nome_do_arquivo_gerado> <0 ou 1>\n", argv[0]);
    exit(0);
  }

  while((c = fgetc(file)) != EOF){
    if(isdigit(c)){
      lin[lin_i++] = c - '0';
      if(lin_i >= lin_len && !mat_i)
	lin = safe_realloc(lin, (lin_len += lin_len) * sizeof *lin);
    }
    else if(c == '\n'){
      if(!mat_i)
	lin_len = lin_i;
      mat[mat_i++] = lin;
      lin = safe_malloc(lin_len * sizeof *lin);
      if(mat_i >= mat_len)
	mat = safe_realloc(mat, (mat_len += mat_len) * sizeof *mat);
      lin_i = 0;
    }
  }
  mat_len = mat_i;
  
  for(mat_i = 0; mat_i < mat_len - 1; mat_i++){
    for(lin_i = mat_i + 1; lin_i < lin_len; lin_i++){
      if(mat[mat_i][lin_i] != mat[lin_i][mat_i]){
	mat[mat_i][lin_i] = argv[2][0] - '0';
	mat[lin_i][mat_i] = argv[2][0] - '0';
      }
    }
  }

  rewind(file);
  for(mat_i = 0; mat_i < mat_len; mat_i++){
    for(lin_i = 0; lin_i < lin_len; lin_i++)
      fprintf(file, "%d ", mat[mat_i][lin_i]);
    fprintf(file, "\n");
  }

  fclose(file);
  return 0;
}
