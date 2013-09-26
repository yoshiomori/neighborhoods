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
#include "word_table.h"

Data data;

int main(int argc, char **argv){
  int i, j;
  node n, stop;
  FILE *file;

  /* Leitura dos dados */
  read_data(argc, argv);

  /* Processando dados */
  processing();

  /* Impressão */
  file = fopen("out.txt", "w");
  for(i = 0; i < data.vertice_head.first_free_pos; i++){
    fprintf(file, "%d: ", data.vertice_head.vertice[i].line);
    for(j = 0; j < data.vertice_head.vertice[i].neighborhood.size; j++){
      fprintf(file, "%d, ", data.vertice_head.vertice[i].neighborhood.vertice[j]->line);
    }
    fprintf(file, "\n");
    if(data.vertice_head.vertice[i].neighborhood.size){
      for(n = data.vertice_head.vertice[i].neighborhood.table->word_vert_neig, stop = n + data.vertice_head.vertice[i].neighborhood.table->length_vert_neig; n != stop; n++)
	if(n->not_null)
	  print_all_vert_neig(n, data.vertice_head.vertice[i].neighborhood.table, file);
    }
    else
      for(n = data.vertice_head.vertice[i].neighborhood.table->word_vert_neig, stop = n + data.vertice_head.vertice[i].neighborhood.table->length_vert_neig; n != stop; n++)
	if(n->not_null){
	  print_vert_neig(n->pos_word, data.vertice_head.vertice[i].neighborhood.table, file);
	  fprintf(file, " : %f\n", (float)n->num_occur / (float)data.vertice_head.vertice[i].size_info);
	}
    fprintf(file, "\n\n");
  }

  return 0;
}
