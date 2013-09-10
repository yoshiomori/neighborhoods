#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "word_table_neig.h"

extern Data data;

void processing(){
  int i = 0, j = 0, k;
  /* int subset = 0; */
  int stop = 1;

  /* Calculo da vizinhança para cada vertice
   */
  for(i = 0; i < data.vertice_head.first_free_pos; i++){
    for(j = 0; j < data.vertice_head.vertice[i].neighborhood.size; j++)
      stop <<= 1;
    
    /* Percorrendo todos os conjuntos do conjunto potencia formado
     * pela vizinhança de do vértice data.vertice_head.vertice[i]
     */
    for(k = 1; k < stop; k++);
  }
}
