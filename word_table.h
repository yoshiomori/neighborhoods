#ifndef WORD_TABLE_NEIG_H
#define WORD_TABLE_NEIG_H

word_table word_table_init(int);
void neig_insert(int, word_table);
void vert_neig_insert(int, word_table);
void print_vert_neig(int, word_table);
void print_neig(int, word_table);
node neig_search(int,word_table);

#endif /* WORD_TABLE_NEIG_H */
