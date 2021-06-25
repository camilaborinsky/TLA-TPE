#ifndef TYPES_H
#define TYPES_H

typedef enum var_type{tINT=0, tDOUBLE, tBOOL, tTEXT, tRECTANGLE, tLINE, tCIRCLE, tDOT}var_type;


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
    int scope;
} variable;



#endif