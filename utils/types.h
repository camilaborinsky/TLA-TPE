#ifndef TYPES_H
#define TYPES_H


typedef enum var_type{tINT=0, tDOUBLE, tBOOL, tTEXT, tRECTANGLE, tLINE, tCIRCLE, tDOT}var_type;

typedef enum operators{ADD = 0, SUB, MUL, DIV, LESS, GREATER, LESSEQ, GREATEQ,EQUALS,NEQ} operators;

typedef union{
    int int_val;
    char * text_val;
    char bool_val;
    double double_val;
    void * class_val;
} variable_value;

typedef struct variable {
    char * name;
    var_type type;
    variable_value value;
    //agregar padding??
} variable;

typedef struct param_type_node{
    struct param_type_node * next;
    var_type type;
}param_type_node;

typedef struct function {
    char * name;
    var_type return_type;
    int param_qty;
    struct param_type_node * first;
} function;



#endif