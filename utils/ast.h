#ifndef AST_H
#define AST_H

typedef enum node_type{
    ROOT,
    DECLARATION_N,
    CONSTANT_N,
    CTL_N,
    LOOP_N,
    ARITHMETIC_N,
    FUNCALL_N,
    FUNDECL_N,
}node_type;

typedef struct ast_node_t{
    node_type type;
    ast_node_t ** children;
    

}ast_node_t;

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
    int string;
}int_node_t;


typedef struct declaration_node_t{
    node_type type;
    
}declaration_node_t;

#define PADDING_SIZE sizeof(if_node_t)
typedef struct node_t{
    node_type type;
    char padding[PADDING_SIZE];
} node_t;


#endif