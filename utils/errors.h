#ifndef ERRORS_H
#define ERRORS_H
#include "types.h"

void multiple_declaration(char * var1, int var, int lineno);
void incompatible_types_operation(var_type type1, var_type type2, char op, int lineno);
void incompatible_types_function(var_type type1, var_type type2, char * function_name, int lineno);
void incompatible_types(var_type type1, var_type type2, int lineno);
void undefined_reference(char* var_name, int lineno);
void illegal_operation(var_type type, char operator, int lineno);
void incompatible_return_type(var_type type1, var_type type2, char * function, int lineno);
void incompatible_parameter_count(int real_qty, int expected_qty,char * function, int lineno);

#endif