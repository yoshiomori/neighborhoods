/* A função main recebe como argumento:                                      *
 *     Um arquivo contendo matriz de dados, matriz de possíveis vizinhos e o *
 * alfabeto, de acordo com o arquivo_padrão;                                 *
 *     Uma constante c para o calculo da vizinhança.                         *
 *                                                                           *
 * A função main retorna:                                                    *
 *     Um arquivo contendo a matriz da vizinhança.                           */

#include <stdio.h>
#include "data.h"
#include "processing.h"

Data data;

int main(int argc, char **argv){
  int i, j;

  /* Leitura dos dados */
  read_data(argc, argv);

  /* Processando dados */
  processing();

  for(i = 0; i < data.vertice_head.first_free_pos; i++){
    printf("%d: ", data.vertice_head.vertice[i].line);
    for(j = 0; j < data.vertice_head.vertice[i].neighborhood.size; j++){
      printf("%d, ", data.vertice_head.vertice[i].neighborhood.vertice[j]->line);
    }
    printf("\n\n");
  }

  return 0;
}
