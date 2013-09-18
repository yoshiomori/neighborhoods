#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "data.h"
#include "word_table.h"

extern Data data;

void processing(){
  int i = 0, j = 0, k, l, m;
  int stop;
  int pos;
  int size;
  word_table cur, prev, aux_table;
  node aux;

  /* Calculo da vizinhança para cada vertice
   */
  for(i = 0, size = 0; i < data.vertice_head.first_free_pos; i++){

    /* Alocando */
    cur = word_table_init(data.vertice_head.vertice[i].neighborhood.size + 2);
    prev = word_table_init(data.vertice_head.vertice[i].neighborhood.size + 2);

    /* Estabelecendo a tabela anterior */
    prev->set[0] = &data.vertice_head.vertice[i];
    prev->set[1] = NULL;
    /* inserindo palavras, que no caso são só as letras 
     * formadas pela informação do vértice
     */
    for(pos = 0; prev->set[0]->info[pos]; pos++)
      vert_neig_insert(pos, prev);
    /* calculo do primeira verossimilhança */
    for(k = 0; k < prev->length_vert_neig; k++)
      if(prev->word_vert_neig[k].not_null)
	prev->f += (double)prev->word_vert_neig[k].num_occur * log((double)prev->word_vert_neig[k].num_occur / (double)data.vertice_head.vertice[i].size_info);
    prev->f -= data.constant * log((double)data.vertice_head.vertice[i].size_info) / log((double)data.size_alphabet);

    /* Ajuste de parada */
    for(j = 0, stop = 1; j < data.vertice_head.vertice[i].neighborhood.size; j++)
      stop <<= 1;
    
    /* Percorrendo todos os conjuntos do conjunto potencia formado
     * pela vizinhança de do vértice data.vertice_head.vertice[i]
     */
    for(k = 1; k != stop; k++){
      /* pegando a próxima possibilidade da vizinhanca */
      cur->set[0] = &data.vertice_head.vertice[i];
      for(l = 0, m = 1; k >> l; l++)
      	if(k >> l & 1)
      	  cur->set[m++] = cur->set[0]->neighborhood.vertice[l];
      cur->set[m] = NULL;
      cur->f = 0;
      
      /* inserindo palavras na tabela
       */
      for(pos = 0; cur->set[0]->info[pos]; pos++){
	neig_insert(pos, cur);
	vert_neig_insert(pos, cur);
      }
      
      /* calculo da verossimilhança do subconjunto da vizinhança */
      for(l = 0; l < cur->length_vert_neig; l++)
	if(cur->word_vert_neig[l].not_null){
	  aux = neig_search(cur->word_vert_neig[k].pos_word, cur);
	  cur->f += (double)cur->word_vert_neig[k].num_occur * log((double)cur->word_vert_neig[k].num_occur / (double)aux->num_occur);
	  printf("%d / %d\n", cur->word_vert_neig[k].num_occur, aux->num_occur);
	}
      cur->f -= data.constant * pow((double)data.size_alphabet, (double)data.vertice_head.vertice[i].size_info) * log((double)data.vertice_head.vertice[i].size_info) / log((double)data.size_alphabet);

      /* Encontrando a maior verossimilhança */
      if(prev->f < cur->f){
	aux_table = cur;
	cur = prev;
	prev = aux_table;
	size = m - 1;
      }
    }

    free(cur);
    /* prev é a tabela de palavras da vizinhança vencedora */
    data.vertice_head.vertice[i].neighborhood.table = prev;
    free(data.vertice_head.vertice[i].neighborhood.vertice);
    /* referenciando a vizinhança vencedora */
    data.vertice_head.vertice[i].neighborhood.vertice = (prev->set) + 1;
    data.vertice_head.vertice[i].neighborhood.size = size;
  }
}
