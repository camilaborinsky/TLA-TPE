#include "errors.h"
#include <stdio.h>
#include "code_generator.h"

extern char ** types;


void multiple_declaration(char * var1, int var, int lineno){
    fprintf(stderr, "ERROR: Multiple declaration of %s %s in line %d\n\n",var ? "variable" :"function", var1, lineno );
}

void incompatible_types_operation(var_type type1, var_type type2, char op, int lineno){
    fprintf(stderr, "ERROR: Incompatible types %s and %s for operation %c in line %d\n\n",types[type1], types[type1], op, lineno );
}

void incompatible_types_function(var_type type1, var_type type2, char * function_name, int lineno){
    fprintf(stderr, "ERROR: Incompatible types %s and %s for function %s in line %d\n\n",types[type1], types[type1], function_name, lineno );
}

void incompatible_types(var_type type1, var_type type2, int lineno){
    fprintf(stderr, "ERROR: Incompatible types %s and %s in assign operation in line %d\n\n",types[type1], types[type1], lineno );
}

void undefined_reference(char* var_name, int lineno){
    fprintf(stderr, "ERROR: Undefined reference to %s in line %d\n\n",var_name, lineno );
}

void illegal_operation(var_type type, char operator, int lineno){
    fprintf(stderr, "ERROR: Illegal operation %c for type %s in line %d\n\n",operator, types[type], lineno );
}

void incompatible_return_type(var_type type1, var_type type2, char * function, int lineno){
    fprintf(stderr, "ERROR: Conflicting types %s and %s for return in function %s in line %d\n\n",types[type1], types[type2], function, lineno );
}

void incompatible_parameter_count(int real_qty, int expected_qty,char * function, int lineno){
    fprintf(stderr, "ERROR: Expected %d parameters but found %d for function %s in line %d\n\n",expected_qty, real_qty, function, lineno );

}

