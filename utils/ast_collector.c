#include "ast_collector.h"
#include <stdlib.h>


//Functions that deal with concluding memory allocation for abstract syntax tree nodes

void collect_ast(root_node_t * root){
    collect_list(root->functions);
    collect_list(root->global_variables);
    collect_list(root->main);
    free(root);
}

void free_variable(variable * variable){
    free(variable->name);
    free(variable);
}

void free_function(function * function){
    free(function->name);
    param_type_node * aux = function->first;
    param_type_node * param = function->first;
    while(param != NULL){
        aux = param;
        free(aux);
        param = param->next;

    }   
    collect_list(function->first);
    free(function);
}

void collect_list(list_node_t * list){
    list_node_t * aux;
    while(list != NULL){
        aux = list;
        list=list->next;
        collectors[aux->node->type](aux->node);
        free(aux);
    }
}


void collect_declaration_code(declaration_node_t * node){
    free_variable(node->var);
    free(node);
}

void collect_constant(const_node_t * node){
    free(node);
}

void collect_if_code(if_node_t * node){
    collectors[node->condition->type](node->condition);
    collect_list(node->then);
    free(node);
}


void collect_loop_code(while_node_t * node){
    collectors[node->condition->type](node->condition);
    collect_list(node->routine);
    free(node);
}

void collect_function_call(func_call_node_t * node){
    free(node->name);
    collect_list(node->params);
    free(node);
}

void collect_function_declaration(function_node_t * node){
    free_function(node->function);
    collect_list(node->parameters);
    collect_list(node->code);
    free(node);
}

void collect_assign_code(assign_node_t * node){
    collectors[node->expression->type](node->expression);
    free(node);
}


void collect_variable(variable_node_t * node){
    free(node);
}


void collect_expression_code(compound_expression_node_t * node){
    collectors[node->left->type](node->left);
    collectors[node->right->type](node->right);
    free(node);
}

void collect_return_code(return_node_t * node){
    collectors[node->expression->type](node->expression);
    free(node);

}

