#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "data.h"
#include "word_table.h"

extern Data data;

void processing(){
  int i = 0, j = 0, k, l, m;
  int stop = 1;
  int pos;
  word_table cur, prev;

  /* Calculo da vizinhança para cada vertice
   */
  for(i = 0; i < data.vertice_head.first_free_pos; i++){

    /* Alocando */
    cur = word_table_init(data.vertice_head.vertice[i].neighborhood.size + 2);
    prev = word_table_init(data.vertice_head.vertice[i].neighborhood.size + 2);

    /* Ajuste de parada */
    for(j = 0; j < data.vertice_head.vertice[i].neighborhood.size; j++)
      stop <<= 1;

    /* Estabelecendo a tabela anterior */
    prev->set[0] = &data.vertice_head.vertice[i];
    prev->set[1] = NULL;
    /* inserindo palavras, que no caso são só as letras 
     * formadas pela informação do vértice
     */
    for(pos = 0; prev->set[0]->info[pos]; pos++)
      word_table_insert(pos, prev);
    /* calculo do primeira verossimilhança */
    for(k = 0; k < prev->length_vert_neig; k++)
      if(prev->word_vert_neig[k].not_null){
	printf("%d / %d \n", prev->word_vert_neig[k].num_occur, data.vertice_head.vertice[i].size_info);
	prev->f += log((double)prev->word_vert_neig[k].num_occur / (double)data.vertice_head.vertice[i].size_info);
      }
    prev->f -= data.constant * log((double)data.vertice_head.vertice[i].size_info) / log((double)data.size_alphabet); 
    printf("%f\n", prev->f);
    printf("next\n\n");
    
    
    /* Percorrendo todos os conjuntos do conjunto potencia formado
     * pela vizinhança de do vértice data.vertice_head.vertice[i]
     */
    for(k = 1; k != stop; k++){
      /* pegando a próxima possibilidade da vizinhanca */
      cur->set[0] = &data.vertice_head.vertice[i];
      for(l = 0, m = 1; k >> l; l++)
	if(k >> l & 1){
	  cur->set[m++] = data.vertice_head.vertice[i].neighborhood.vertice[l];
	}
      cur->set[m] = NULL;
      /* inserindo palavras na tabela
       */
    };

    free(cur);
    /* prev é a tabela de palavras da vizinhança vencedora */
    data.vertice_head.vertice[i].neighborhood.table = prev;
    free(data.vertice_head.vertice[i].neighborhood.vertice);
    /* referenciando a vizinhança vencedora */
    data.vertice_head.vertice[i].neighborhood.vertice = (prev->set) + 1;
  }
}
