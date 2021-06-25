#include "ast.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>

int_node_t * new_int_node(int value){
    int_node_t * new_node = calloc(1, sizeof(int_node_t));
    new_node->type = INT_N;
    new_node->value = value;
    return new_node;
}

declaration_node_t * new_declaration_node(char * var_name,var_type type){
    variable * var=calloc(1, sizeof(variable));
    var->name = calloc(1, strlen(var_name));
    strcpy(var->name, var_name);
    var->type = type;
    if(insert( var ) < 0 ){
         //error variable already defined
         free(var->name);
         free(var);
    }
    declaration_node_t * new_node = calloc(1, sizeof(declaration_node_t));
    new_node->type = DECLARATION_N;
    new_node->var = var;
    return new_node;

}

assign_node_t* new_assign_node(char * variable_name, expression_node_t*  expression){ //TODO: ver tema de que tipo es este expression node
    variable * var = lookup(variable_name);
    if(var == NULL){
        //variable not defined in scope ERROR
    }else if(var->type != expression->expression_type){
        //conflicting types ERROR
    }

    assign_node_t * new_node = calloc(1, sizeof(assign_node_t));
    new_node->type = ASSIGN_N;
    new_node->var = var;
    new_node->expression = expression;
    return new_node;
    
}

variable_node_t* new_var_node(char * variable_name){
    variable * var = lookup(variable_name);
    if(var == NULL){
        //undefined reference to variable 
    }
    variable_node_t * var_node = calloc(1, sizeof(variable_node_t));
    var_node->type = VARIABLE_REF_N;
    var_node->var_type = var->type;
    var_node->var = var;
    return var_node;
}

const_node_t* new_const_node(variable_value * value){
    const_node_t * const_node = calloc(1, sizeof(const_node_t));
    const_node->type = CONSTANT_N;
    const_node->value = value;
    return const_node;
}
