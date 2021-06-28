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
    void collect_decl_assign_code(decl_assign_node_t * node);
    
    void collect_list(list_node_t *);


#endif
