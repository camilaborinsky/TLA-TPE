#include "code_generator.h"
#include "ast.h"
#include <stdio.h>

typedef enum node_type{
    ROOT = 0,
    DECLARATION_N,
    CONSTANT_N,
    CTL_N,
    LOOP_N,
    FUNCALL_N,
    FUNDECL_N,
    ASSIGN_N,
    VARIABLE_REF_N,
    EXPRESSION_N,
    CONDITION_N,
    
}node_type;

void dummy(ast_node_t *);
void generate_declaration_code(declaration_node_t * declaration_node);
void generate_constant(ast_node_t constant);
void generate_if_code(if_node_t * if_node);
void generate_loop_code(while_node_t * loop_node);
void generate_function_call(ast_node_t * node);
void generate_function_declaration(ast_node_t * node);
void generate_assign_code(assign_node_t * assign_node);
void generate_variable(ast_node_t * node);
void generate_expression_code(expression_node_t * expression_node);
void generate_condition_code(condition_node_t * condition_node);


void (*generators[])(ast_node_t * node) = {
    dummy, //root
    generate_declaration_code,
    generate_constant,
    generate_if_code,
    generate_loop_code,
    generate_function_call,
    generate_function_declaration,
    generate_assign_code,
    generate_variable,
    generate_expression_code,
    generate_condition_code,

};

void generate_list(list_node_t * list);

void generate_code(root_node_t * tree){
    generate_initial_setup();
    generate_list(tree->global_variables);
    generate_list(tree->functions);
    generate_list(tree->main);


}

void generate_list(list_node_t * list){
    while(list != NULL){
        generators[list->node->type](list->node);
    }
}


void generate_initial_setup(){
    printf("#include<stdlib.h>\n #include<stdio.h>\n #include<strings.h>\n");
}

void generate_if_code(if_node_t * if_node){
    printf("if(");
    generate_condition_code(if_node->condition);
    printf("){");
    generate_main_code(if_node->then);
    printf("}");
    free(if_node);
}

void generate_loop_code(while_node_t * loop_node){
    printf("while(");
    generate_condition_code(loop_node->condition);
    printf("){");
    generate_main_code(loop_node->routine);
    printf("}");
    free(loop_node);
}

void generate_declaration_code(declaration_node_t * declaration_node){
    generate_type_code(declaration_node->var->type);
    printf("%s;", declaration_node->var->name);
    free(declaration_node);
}

void generate_assign_code(assign_node_t * assign_node){
    printf("%s = ", assign_node->var->name);
    generate_expression_code(assign_node->expression);
    free(assign_node);
}

void generate_expression_code(expression_node_t * expression_node){
    
}

void generate_condition_code(condition_node_t * condition_node){

}
void generate_main_code(list_node_t * instructions){

}