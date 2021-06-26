#include "ast.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>

root_node_t * new_root_node(){
    root_node_t *  node = calloc(1,sizeof(root_node_t));
    node->type=ROOT;
    init_symbol_table();
    return node;
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



if_node_t* new_if_node(condition_node_t * condition,list_node_t*  code){
    if_node_t * if_node = calloc(1, sizeof(if_node_t));
    if_node->type = CTL_N;
    if_node->condition = condition;
    if_node->then = code;
    return if_node;
}

while_node_t* new_loop_node(condition_node_t * condition,list_node_t*  code){
    while_node_t * loop_node = calloc(1, sizeof(while_node_t));
    loop_node->type = LOOP_N;
    loop_node->condition = condition;
    loop_node->routine = code;
    return loop_node;
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


condition_node_t* new_compose_cond_node(condition_node_t * left, char  operator,condition_node_t * right){
    condition_node_t * condition_node = calloc(1, sizeof(condition_node_t));
    condition_node->type = CONDITION_N;
    condition_node->left = left;
    condition_node->right = right;
    condition_node->operator = operator;
    return condition_node;
}

condition_node_t * not_cond(condition_node_t * right){
    condition_node_t * condition_node = calloc(1, sizeof(condition_node_t));
    condition_node->type = CONDITION_N;
    condition_node->right = right;
    condition_node->operator = '!';
    return condition_node;

}

expression_node_t* new_compose_expr_node(expression_node_t * left,char operator,expression_node_t * right){
    compound_expression_node_t * expression_node = calloc(1, sizeof(condition_node_t));
    expression_node->type = EXPRESSION_N;
    if(left->expression_type != right->expression_type){
        //error with incompatible types
    }
    expression_node->expression_type = left->expression_type;
    expression_node->left = left;
    expression_node->right = right;
    expression_node->operator = operator;
    return expression_node;
}




/* Terminal nodes */

const_node_t* new_const_node(variable_value value){
    const_node_t * const_node = calloc(1, sizeof(const_node_t));
    const_node->type = CONSTANT_N;
    const_node->value = value;
    return const_node;
}

true_node_t * new_true_node(){
    true_node_t * true_node = calloc(1, sizeof(true_node_t));
    true_node->type = TRUE_N;
    return true_node;
}

false_node_t * new_false_node(){
    false_node_t * false_node = calloc(1, sizeof(false_node_t));
    false_node->type = FALSE_N;
    return false_node;
}


int_node_t * new_int_node(int value){
    int_node_t * new_node = calloc(1, sizeof(int_node_t));
    new_node->type = INT_N;
    new_node->value = value;
    return new_node;
}

string_node_t * new_string_node(char * value){
    string_node_t * string_node = calloc(1, sizeof(string_node_t));
    string_node->type = STRING_N;
    string_node->string = value;
}

list_node_t * new_param_decl_node(char * name, var_type type){
    list_node_t * params = calloc(1, sizeof(list_node_t));
    declaration_node_t * decl_node = new_declaration_node(name, type);
    params->node = decl_node;
    return params;
}

function_node_t * new_function_node(var_type type, char * name, list_node_t * params, list_node_t * code){
    function_node_t * function = calloc(1, sizeof(function_node_t));
    function->type = FUNDECL_N;
    function->code = code;
    function->parameters = params;
    function->return_type = type;

}


list_node_t * new_param_node(char * name){
    list_node_t * params = calloc(1, sizeof(list_node_t));
    variable_node_t * var_node = new_var_node(name);
    params->node = var_node;
    return params;
}




/* ADD NODE FUNCTIONS*/

// void add_decl_node(list_node_t * global_variables, declaration_node_t * declaration_node){
//     list_node_t * new_node = calloc(1, sizeof(list_node_t));
//     new_node->node = declaration_node;
//     new_node->next = global_variables;
//     global_variables = new_node;
// }

// void add_func_node(list_node_t * functions, function_node_t * function_node){
//     list_node_t * new_node = calloc(1, sizeof(list_node_t));
//     new_node->node = function_node;
//     new_node->next = functions;
//     functions = new_node;

// }


list_node_t * concat_node(list_node_t * list, ast_node_t * code ){
    list_node_t * new_node = calloc(1, sizeof(list_node_t));
    new_node->node = code;
    new_node->next = list;
    list = new_node;
    return list;
}

list_node_t * concat_lists(list_node_t * main, list_node_t * instructions){
    list_node_t * aux = main;
    while(aux->next != NULL ) aux = aux->next;
    aux->next = instructions;
    return aux;
    

}

