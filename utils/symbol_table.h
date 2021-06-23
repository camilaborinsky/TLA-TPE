
typedef enum var_type{INT=0, DOUBLE, BOOL, TEXT, RECTANGLE, LINE, CIRCLE, DOT}var_type;

#define MULTIPLE_DECLARATION -1;
#define OUT_OF_SCOPE =-2;

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


void init_table();
unsigned long long hash(char * name);
int insert(char * name, var_type type);
variable * lookup(char * name);
variable * lookup_in_scope(char * name, int scope);
void next_scope();
void prev_scope();

