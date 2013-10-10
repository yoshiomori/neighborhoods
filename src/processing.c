#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "data.h"
#include "word_table.h"
#include "vertice.h"

extern Data data;

void processing(){
  int i = 0, j = 0, k, l, m;
  int stop;
  int pos;
  int size;
  word_table cur, prev, aux_table;
  node aux, aux_stop;
  /* Vertice v, aux_v, *mod; */

  /* Calculo da vizinhança para cada vertice
   */
  for(i = 0; i < data.vertice_head.first_free_pos; i++){
    size = 0;

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
      /* Limpando a tabela de palavras cur */
      cur->f = 0;
      cur->free_neig = cur->length_neig;
      cur->free_vert_neig = cur->length_vert_neig;
      for(aux = cur->word_vert_neig, aux_stop = aux + cur->length_vert_neig; aux < aux_stop; aux++){
	if(aux->not_null){
	  aux->not_null = 0;
	  aux->num_occur = 0;
	}
      }
      for(aux = cur->word_neig, aux_stop = aux + cur->length_neig; aux < aux_stop; aux++){
	if(aux->not_null){
	  aux->not_null = 0;
	  aux->num_occur = 0;
	}
      }
      /* pegando a próxima possibilidade da vizinhanca */
      cur->set[0] = &data.vertice_head.vertice[i];
      for(l = 0, m = 1; k >> l; l++)
      	if(k >> l & 1)
      	  cur->set[m++] = cur->set[0]->neighborhood.vertice[l];
      cur->set[m] = NULL;
      
      /* inserindo palavras na tabela
       */
      for(pos = 0; cur->set[0]->info[pos]; pos++){
	neig_insert(pos, cur);
	vert_neig_insert(pos, cur);
      }
      
      /* calculo da verossimilhança do subconjunto da vizinhança */
      for(l = 0; l < cur->length_vert_neig; l++)
      	if(cur->word_vert_neig[l].not_null){
      	  aux = neig_search(cur->word_vert_neig[l].pos_word, cur);
      	  cur->f += (double)cur->word_vert_neig[l].num_occur * log((double)cur->word_vert_neig[l].num_occur / (double)aux->num_occur);
      	}
      cur->f -= data.constant * pow((double)data.size_alphabet, (double)(m-1)) * log((double)data.vertice_head.vertice[i].size_info) / log((double)data.size_alphabet);

      /* Encontrando a maior verossimilhança */
      if(prev->f <= cur->f){
      	aux_table = cur;
      	cur = prev;
      	prev = aux_table;
      	size = m - 1;
      }
    }

    if(cur){
      free(cur);
      cur = NULL;
    }
    /* prev é a tabela de palavras da vizinhança vencedora */
    data.vertice_head.vertice[i].neighborhood.table = prev;
    if(data.vertice_head.vertice[i].neighborhood.vertice){
      free(data.vertice_head.vertice[i].neighborhood.vertice);
      data.vertice_head.vertice[i].neighborhood.vertice = NULL;
    }
    /* referenciando a vizinhança vencedora */
    data.vertice_head.vertice[i].neighborhood.vertice = (prev->set) + 1;
    data.vertice_head.vertice[i].neighborhood.size = size;
  }

  /* /\* Criando simetria entre a vizinhaça, exemplo: */
  /*  * 2: 0, 1, 3 */
  /*  * 4: 2 */
  /*  * Então */
  /*  * 2: 0, 1, 3, 4 */
  /*  * 4: 2 */
  /*  *\/ */
  /* mod = calloc(data.vertice_head.first_free_pos, sizeof *mod); */
  /* for(i = 0; i < data.vertice_head.first_free_pos; i++) */
  /*   for(j = 0; j < data.vertice_head.vertice[i].neighborhood.size; j++) */
  /*     if(!neighborhood_search(&(data.vertice_head.vertice[i]), data.vertice_head.vertice[i].neighborhood.vertice[j]->neighborhood)){ */
  /* 	/\* Corrigindo a vizinhaça *\/ */
  /* 	for(k = 0, v = &(data.vertice_head.vertice[i]); k < data.vertice_head.vertice[i].neighborhood.vertice[j]->neighborhood.size; k++) */
  /* 	  if(v < data.vertice_head.vertice[i].neighborhood.vertice[j]->neighborhood.vertice[k]){ */
  /* 	    aux_v = v; */
  /* 	    v = data.vertice_head.vertice[i].neighborhood.vertice[j]->neighborhood.vertice[k]; */
  /* 	    data.vertice_head.vertice[i].neighborhood.vertice[j]->neighborhood.vertice[k] = aux_v; */
  /* 	  } */
  /* 	data.vertice_head.vertice[i].neighborhood.vertice[j]->neighborhood.vertice[k] = v; */
  /* 	data.vertice_head.vertice[i].neighborhood.vertice[j]->neighborhood.vertice[k + 1] = NULL; */
  /* 	data.vertice_head.vertice[i].neighborhood.vertice[j]->neighborhood.size++; */
  /* 	mod[j] = data.vertice_head.vertice[i].neighborhood.vertice[j]; */
  /*     } */

  /* /\* Recriando tabela *\/ */
  /* for(i = 0; i < data.vertice_head.first_free_pos; i++){ */
  /*   if(mod[i]){ */
  /*     /\* Limpando a tabela de palavras *\/ */
  /*     mod[i]->neighborhood.table->free_neig = mod[i]->neighborhood.table->length_neig; */
  /*     mod[i]->neighborhood.table->free_vert_neig = mod[i]->neighborhood.table->length_vert_neig; */
  /*     for(aux = mod[i]->neighborhood.table->word_vert_neig, aux_stop = aux + mod[i]->neighborhood.table->length_vert_neig; aux < aux_stop; aux++){ */
  /* 	if(aux->not_null){ */
  /* 	  aux->not_null = 0; */
  /* 	  aux->num_occur = 0; */
  /* 	} */
  /*     } */
  /*     for(aux = mod[i]->neighborhood.table->word_neig, aux_stop = aux + mod[i]->neighborhood.table->length_neig; aux < aux_stop; aux++){ */
  /* 	if(aux->not_null){ */
  /* 	  aux->not_null = 0; */
  /* 	  aux->num_occur = 0; */
  /* 	} */
  /*     } */
  /*     for(pos = 0; mod[i]->neighborhood.table->set[0]->info[pos]; pos++){ */
  /* 	neig_insert(pos, mod[i]->neighborhood.table); */
  /* 	vert_neig_insert(pos, mod[i]->neighborhood.table); */
  /*     } */
  /*   } */
  /* } */
}
