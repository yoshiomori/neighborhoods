#ifndef DATA_H
#define DATA_H

typedef struct VERTICE *Vertice;
struct VERTICE{
  char **info;
  Vertice *neighborhood;
};

typedef struct DATA{
  char **alphabet;
  float constant;
  struct Vertice_Head{
    Vertice vertice;
    int length;
    int first_free_pos;
  }vertice_head;
}Data;

void read_data(int, char**);
char **chop(char *);

#endif /* DATA_H */
