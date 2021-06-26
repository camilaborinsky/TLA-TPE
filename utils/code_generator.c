#include "code_generator.h"
#include <stdio.h>

void generate_code(root_node_t * tree){
    generate_initial_setup();


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

void generate_expresion_code(expression_node_t * expression_node){
    
}

void generate_condition_code(condition_node_t * condition_node){

}
void generate_main_code(list_node_t * instructions){

}