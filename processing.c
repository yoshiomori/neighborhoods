#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "word_table.h"

extern Data data;

void processing(){
  int i = 0, j = 0, k;
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
    
    /* Percorrendo todos os conjuntos do conjunto potencia formado
     * pela vizinhança de do vértice data.vertice_head.vertice[i]
     */
    for(k = 1; k != stop; k++);

    free(cur);
    /* prev é a tabela de palavras da vizinhança vencedora */
    data.vertice_head.vertice[i].neighborhood.table = prev;
    free(data.vertice_head.vertice[i].neighborhood.vertice);
    /* referenciando a vizinhança vencedora */
    data.vertice_head.vertice[i].neighborhood.vertice = (prev->set) + 1;
  }
}
