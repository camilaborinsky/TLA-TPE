#ifndef SYMBOL_H
#define SYMBOL_H
#include "types.h"


#define MULTIPLE_DECLARATION -1;
#define OUT_OF_SCOPE =-2;



void init_table();
unsigned long long hash(char * name);
int insert(variable* var);
variable * lookup(char * name);
variable * lookup_in_scope(char * name, int scope);
void next_scope();
void prev_scope();

#endif