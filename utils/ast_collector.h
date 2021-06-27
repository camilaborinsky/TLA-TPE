#ifndef COLLECTOR_H
#define COLLECTOR_H

#include "types.h"
#include "ast.h"

    void collect_ast(root_node_t * node); //root
    void collect_declaration_code(declaration_node_t * node);
    void collect_constant(const_node_t * node);
    void collect_if_code(if_node_t * node);
    void collect_loop_code(while_node_t * node);
    void collect_function_call(func_call_node_t * node);
    void collect_function_declaration(function_node_t * node);
    void collect_assign_code(assign_node_t * node);
    void collect_variable(variable_node_t * node);
    void collect_expression_code(compound_expression_node_t * node);
    void collect_return_code(return_node_t * node);


void (*collectors[])(ast_node_t * node) = {
    collect_ast, //root
    collect_declaration_code,
    collect_constant,
    collect_if_code,
    collect_loop_code,
    collect_function_call,
    collect_function_declaration,
    collect_assign_code,
    collect_variable,
    collect_expression_code,
    collect_return_code,

};





#endif
