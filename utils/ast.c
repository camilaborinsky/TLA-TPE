#include "ast.h"
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
         fprintf(stderr, "Ya existe una variable definida con ese nombre\n");
         free(var->name);
         free(var);
         return NULL;
    }
    declaration_node_t * new_node = calloc(1, sizeof(declaration_node_t));
    new_node->type = DECLARATION_N;
    new_node->var = var;
    return new_node;

}

assign_node_t* new_assign_node(char * variable_name, expression_node_t*  expression){ //TODO: ver tema de que tipo es este expression node
    variable * var = lookup(variable_name);
    if(var == NULL){
        fprintf(stderr, "Referencia a variable inexistente.\n");
        return NULL;
    }else if(var->type != expression->expression_type){
        fprintf(stderr, "Incompatibilidad de tipos en asignación.\n");
        return NULL;
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
        fprintf(stderr, "Referencia a variable inexistente.\n");
        return NULL;
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
    if(left->expression_type != right->expression_type){
        fprintf(stderr, "Incompatibilidad de tipos en la expresión.\n");
        return NULL;
    }
    if(left->expression_type > tDOUBLE){
        fprintf(stderr, "Operación \'%c\' no permitida para el tipo solicitado.\n", operator);
        return NULL;

    }
    compound_expression_node_t * expression_node = calloc(1, sizeof(compound_expression_node_t));
    expression_node->type = EXPRESSION_N;
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

const_node_t * new_true_node(){
    const_node_t * const_node = calloc(1, sizeof(const_node_t));
    const_node->type = CONSTANT_N;
    const_node->constant_type = tBOOL;
    const_node->value.bool_val=1;
    return const_node;
}

const_node_t * new_false_node(){
    const_node_t * const_node = calloc(1, sizeof(const_node_t));
    const_node->type = CONSTANT_N;
    return const_node;
}


const_node_t * new_int_node(int value){
    const_node_t * const_node = calloc(1, sizeof(const_node_t));
    const_node->type = CONSTANT_N;
    const_node->constant_type=tINT;
    const_node->value.int_val = value;
    return const_node;
}

const_node_t * new_double_node(double value){
    const_node_t * const_node = calloc(1, sizeof(const_node_t));
    const_node->type = CONSTANT_N;
    const_node->constant_type=tDOUBLE;
    const_node->value.double_val = value;
    return const_node;
}

const_node_t * new_string_node(char * value){
    const_node_t * string_node = calloc(1, sizeof(const_node_t));
    string_node->type = CONSTANT_N;
    string_node->constant_type = tTEXT;
    string_node->value.text_val = value;
}

list_node_t * new_param_decl_node(char * name, var_type type){
    list_node_t * params = calloc(1, sizeof(list_node_t));
    declaration_node_t * decl_node = new_declaration_node(name, type);
    params->node = decl_node;
    return params;
}

function_node_t * new_function_node(var_type type, char * name, list_node_t * params, list_node_t * code){
   
    function * func = calloc(1, sizeof(function));
    func->name = name;
    func->return_type = type;
    if(insert((variable*) func) < 0){
        fprintf(stderr, "Ya existe una función definida con ese nombre.\n");
        free(name);
        free(func);
        return NULL;
    }
    int param_qty = 0;
    list_node_t * aux = params;
    while (aux != NULL){
        param_qty ++;
        param_type_node * new_node = calloc(1,sizeof(param_type_node));
        new_node->type = aux->node->type;
        new_node->next = func->first;
        func->first=new_node; 
        aux = aux->next;
    }
    func -> param_qty = param_qty;
    
    function_node_t * func_node = calloc(1, sizeof(function_node_t));
    func_node->type = FUNDECL_N;
    func_node->function = func;
    func_node->code = code;
    func_node->parameters = params;

}

func_call_node_t * new_function_call_node(char * name, list_node_t * params){
    function * function = lookup(name);
    if(function == NULL){
        fprintf(stderr, "No existe función definida con ese nombre.\n");
        free(name);
        return NULL;

    }
    func_call_node_t * func_call_node = calloc(1,sizeof(func_call_node_t));
    func_call_node->type=FUNCALL_N;
    list_node_t * aux=params;
    param_type_node * aux_type=function->first;
    while(aux != NULL){
        if(aux_type == NULL){
            fprintf(stderr, "Incompatibilidad en la cantidad de parámetros de la llamada a la función '%s' y su declaración.\n",name);
            free(func_call_node);
            return NULL;
        }
        if(params->node->type != aux_type->type){
            fprintf(stderr, "Incompatibilidad de tipos en los parámetros de la llamada a la función \'%s\'y su declaración.\n",name);
            return NULL;
        }else{
            aux=aux->next;
            aux_type = aux_type->next;
        }
    }
    if( aux_type == NULL){
        fprintf(stderr, "Incompatibilidad de tipos en los parámetros de la llamada a la función \'%s\'y su declaración.\n",name);
        return NULL;
        //ERROR: PARAMETROS DE MAS EN LA LLAMADA A LA FUNCION
    }
    func_call_node->name=name;
    func_call_node->params=params;
    
}



//eSTO ESTA MAL
list_node_t * new_param_node(expression_node_t * expression_node){
    list_node_t * params = calloc(1, sizeof(list_node_t));
    params->node->type = EXPRESSION_N;
    params->node = expression_node;
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

