#ifndef AST_H
#define AST_H
#include "types.h"

typedef enum node_type{
    ROOT,
    DECLARATION_N,
    CONSTANT_N,
    CTL_N,
    LOOP_N,
    ARITHMETIC_N,
    FUNCALL_N,
    FUNDECL_N,
    INT_N,
    STRING_N,
    ASSIGN_N,
    VARIABLE_REF_N,
    EXPRESSION,
    
}node_type;

typedef struct list_node_t{
    ast_node_t * node;
    ast_node_t * next;
}list_node_t;

typedef struct root_node_t{
    node_type type;
    list_node_t* global_variables;
    list_node_t* functions;
    list_node_t* main;
}root_node_t;


typedef struct if_node_t{
    node_type type;
    ast_node_t * condition;
    ast_node_t * then;
}if_node_t;


typedef struct while_node_t{
    node_type type;
    ast_node_t * condition;
    ast_node_t * routine;
}while_node_t;

typedef struct string_node_t{
    node_type type;
    char * string;
}string_node_t;

typedef struct int_node_t{
    node_type type;
    int value;
}int_node_t;

typedef struct declaration_node_t{
    node_type type;
    variable * var;
    
}declaration_node_t;

typedef struct assign_node_t{
    node_type type;
    variable * var;
    expression_node_t * expression;
    
}assign_node_t;

#define PADDING_SIZE sizeof(if_node_t)
typedef struct ast_node_t{
    node_type type;
    char padding[PADDING_SIZE];
} ast_node_t;

typedef struct function_node_t{
    node_type type;
    var_type return_type;
    list_node_t * parameters;
    list_node_t * code;
} function_node_t;

typedef struct true_node_t{
    node_type type;
}true_node_t;

typedef struct false_node_t{
    node_type type;
}false_node_t;
typedef struct condition_node_t{
    node_type type;
}condition_node_t;

typedef struct expression_node_t{
    node_type type;
    var_type expression_type;
}expression_node_t;

typedef struct compound_expression_node_t{
    node_type type;
    var_type expression_type;
    expression_node_t * left;
    expression_node_t * right;
}compound_expression_node_t;

typedef struct variable_node_t{
    node_type type;
    var_type var_type;
    variable * var;
}variable_node_t;

typedef struct const_node_t{
    node_type type;
    var_type constant_type;
    variable_value * value;
}const_node_t;

add_decl_node(list_node_t * global_variables, declaration_node_t * declaration_node);
add_func_node(list_node_t * functions, function_node_t * function_node);
add_instructions(list_node_t * main, list_node_t * instructions );
condition_node_t* new_compose_cond_node(condition_node_t * left, char * operator,condition_node_t * right);
expression_node_t* new_compose_expr_node(expression_node_t * left,char * operator,expression_node_t right);
true_node_t * new_true_node();
false_node_t * new_false_node();
root_node_t new_root_node();
int_node_t * new_int_node(int value);
declaration_node_t * new_declaration_node(variable * var,var_type type);
assign_node_t* new_assign_node(char * name, expression_node_t * expression);
variable_node_t* new_var_node(char * variable);
const_node_t* new_const_node(variable_value * value);
if_node_t* new_if_node(condition_node_t * condition,list_node_t*  code);
while_node_t new_loop_node(condition_node_t * condition,list_node_t*  code);

#endif