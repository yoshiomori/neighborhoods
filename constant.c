#include <stdio.h>
#include <stdlib.h>

#include "glob.h"

extern Data data;

void format_error_constant(){
  printf("Erro no formato da constante no arquivo!\n");
  exit(0);
}

void read_constant(char *line){
  int state = 0;
  float decimal = 1;
  data.constant = 0;
  for(; *line; line++){
    switch(state){
    case 0:
      if('0' <= *line && *line <= '9')
	data.constant = (data.constant *= 10) + (float)(*line - '0');
      else if(*line == '.' || *line == ',')
	state = 1;
      else
	format_error_constant();
      break;
    case 1:
      if('0' <= *line && *line <= '9')
	data.constant += (float)(*line - '0') * (decimal *= 0.1);
      else if(*line == ' ' || *line == '\n')
	state = 2;
      else
	format_error_constant();
      break;
    case 2:
      if(*line != ' ' && *line != '\n')
	format_error_constant();
      break;
    }
  }
}
