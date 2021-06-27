#include "code_generator.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>

void dummy(ast_node_t *);
void generate_declaration_code(declaration_node_t * declaration_node);
void generate_constant(const_node_t * constant);
void generate_if_code(if_node_t * if_node);
void generate_loop_code(while_node_t * loop_node);
void generate_function_call(func_call_node_t * fun_call);
void generate_function_declaration(function_node_t * node);
void generate_assign_code(assign_node_t * assign_node);
void generate_variable(variable_node_t * node);
void generate_expression_code(compound_expression_node_t * expression_node);
void generate_return_code(return_node_t * node);
void generate_decl_assign_code(decl_assign_node_t * node);


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
    generate_return_code,
    generate_decl_assign_code,

};

char * types[] = {"int", "double" ,"bool", "char *" , "rectangle *", "line *", "circle *", "dot *", "figure *", "void"};
char * ops[] = {"+","-","*","/","<",">","<=",">=","==","!=","!","&&","||"};

void generate_list(list_node_t * list);

void generate(ast_node_t * node){
     generators[node->type](node);
}

void dummy(ast_node_t * dummy){};

void generate_code(root_node_t * tree){
    generate_initial_setup();
    generate_list(tree->global_variables);
    generate_list(tree->functions);
    printf("int main(){\n");
    printf("init();\n");
    generate_list(tree->main);
    if(tree->easter_egg)
        printf("easter_egg();\n");
    printf("loop();\nreturn 0;\n}\n\n\n");
}



void generate_list(list_node_t * list){
    list_node_t * prev;
    while(list != NULL){
        generate(list->node);
        prev = list;
        list=list->next;
        //free(prev);
    }
}

void generate_params_list(list_node_t * list){
    list_node_t * prev;
    while(list != NULL){
        generate(list->node);
        if(list->next != NULL ) printf(",");
        prev = list;
        list=list->next;
        //free(prev);
    }
}

void generate_initial_setup(){
    printf(
            "#include<stdlib.h>\n"\
            "#include<stdio.h>\n"\
            "#include<strings.h>\n"\
            "#include\"lib/figures.h\"\n"\
            "#include\"lib/handlers.h\"\n"\
            "\n");
}

void generate_type_code(var_type type){
    printf("%s",types[type]);
}

void generate_if_code(if_node_t * if_node){
    printf("if(");
    generate(if_node->condition);
    printf("){\n");
    generate_list(if_node->then);
    printf("}\n");
}

void generate_loop_code(while_node_t * loop_node){
    printf("while(");
    generate(loop_node->condition);
    printf("){\n");
    generate_list(loop_node->routine);
    printf("}\n");
}


void generate_declaration_code(declaration_node_t * declaration_node){
    generate_type_code(declaration_node->var->type);
    printf(" %s ", declaration_node->var->name);
    if(declaration_node->terminal) printf(";\n");
}

void generate_assign_code(assign_node_t * assign_node){
    printf("%s = ", assign_node->var->name);
    generate(assign_node -> expression);
    printf(";\n");
}

void generate_expression_code(compound_expression_node_t * expression_node){ 
    if(expression_node->closed) printf(" ( ");
    if(expression_node->left != NULL) generate(expression_node->left);
    printf(" %s ", ops[expression_node->operator]);
    generate(expression_node->right);
    if(expression_node->closed) printf(" ) ");
}

void generate_function_call(func_call_node_t * fun_call){
    printf("%s(", fun_call->name);
    generate_params_list(fun_call->params);
    printf(")");
    if(fun_call->terminal) printf(";\n");
}

void generate_function_declaration(function_node_t * node){
    generate_type_code(node->function->return_type);
    printf(" %s(", node->function->name);
    generate_params_list(node->parameters);
    printf("){\n");
    generate_list(node->code);
    printf("}\n");
}

void generate_constant(const_node_t * constant){
    switch (constant->constant_type)
    {
    case tBOOL:
    case tINT:
        printf("%d", constant->value.int_val);
        break;
    case tDOUBLE:
        printf("%f",constant->value.double_val);
        break;
    case tTEXT:
        printf("%s",constant->value.text_val);
        break;
    }
}

void generate_variable( variable_node_t * node){
    printf(" %s ", node->var->name);
    //free(node->var->name);
    //free(node->var);
    //free(node);
}

void generate_return_code(return_node_t * node){
    printf("return ");
    if(node->expression != NULL) generate(node->expression);
    printf(";\n");
}

void generate_decl_assign_code(decl_assign_node_t * node){
    printf("%s %s = ",types[node->var->type],node->var->name);

    generate(node->expression);
    printf(";\n");
}