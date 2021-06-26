#ifndef CODE_GENERATOR_H
#define CODE_GENERATOR_H

#include "ast.h"

void generate_code(root_node_t * tree);

void generate_initial_setup();

void generate_if_code(if_node_t * if_node);
void generate_loop_code(while_node_t * if_node);
void generate_declaration_code(declaration_node_t * if_node);
void generate_assign_code(assign_node_t * assign_node);

void generate_condition_code(condition_node_t * condition_node);



#endif