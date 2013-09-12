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
  int i = 0;
  char **aux = 0;
  
  /* Leitura dos dados */
  read_data(argc, argv);

  /* Processando dados */
  processing();

  return 0;
}
