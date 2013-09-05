/* A função main recebe como argumento:                                      *
 *     Um arquivo contendo matriz de dados, matriz de possíveis vizinhos e o *
 * alfabeto, de acordo com o arquivo_padrão;                                 *
 *     Uma constante c para o calculo da vizinhança.                         *
 *                                                                           *
 * A função main retorna:                                                    *
 *     Um arquivo contendo a matriz da vizinhança.                           */

#include "data.h"
#include <stdio.h>

Data data;

int main(int argc, char **argv){

  /* Leitura dos dados */
  read_data(argc, argv);
  return 0;
}
