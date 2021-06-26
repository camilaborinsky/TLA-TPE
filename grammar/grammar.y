%code requires {
        #include <stdio.h>
        #include <stdlib.h>
        #include "utils/types.h"
        #include "utils/symbol_table.h"
        #include "utils/code_generator.h"
        #include "utils/ast.h"
}

%{
        int yylex();
        void yyerror();
%}

%union{
  char * string;
  int integer;
  float decimal;
  int type;
  variable * var;
  variable_value value;
  ast_node_t * node;
  root_node_t * rnode;
}

%token<string> ID
%token<type> INT DOUBLE BOOL RECTANGLE CIRCLE DOT TEXT LINE
%token IF WHILE FUNCTION LET LE GE EQ NE NOT START RETURN
%token<integer> OR AND
%token<value> vTEXT vINT vDOUBLE TRUE FALSE 
%type <integer> OPERATOR
%type<node> DECL ASSIGN CTL MAIN_CODE LOOP SMP FUNC PARAM_DECL_LIST PARAM_DECL CODE CALL PARAM_LIST PARAM COND CONDITIONAL_OPERATOR EXPRESSION VALUE
%type<rnode> S
%type<type> T
%parse-param {root_node_t * root}
%right "="
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'
%start PROGRAM



%%

PROGRAM   : START  S  RETURN 
          | S {return 0;}

S         : DECL S  {root->global_variables = concat_node(root->global_variables,$1);}
          | FUNC S  {root->functions = concat_node(root->functions, $1);}
          | MAIN_CODE S {root->main = concat_lists(root->main, $1); }
          | {$$ = 0;}
          ;

MAIN_CODE : CTL MAIN_CODE {$$ = concat_node($2,$1); }
          | LOOP MAIN_CODE {$$ = concat_node($2,$1); }
          | SMP MAIN_CODE {$$ = concat_node($2, $1);}
          | {$$ = 0;}
          ;

FUNC  : FUNCTION ID ':' T '(' PARAM_DECL_LIST ')' '{' CODE '}' {$$ = new_function_node($2, $4, $6, $9);}

PARAM_DECL_LIST : PARAM_DECL {$$ = $1;}
                | {$$ = 0;}
                ; 


PARAM_DECL : ID ':' T { $$ = new_param_decl_node($1,$3);}
           | PARAM_DECL ',' PARAM_DECL {$$ = concat_lists($1,$3);}
           ;

CODE      : CTL CODE { $$ = concat_node($2,$1); }
          | LOOP CODE {$$ = concat_node($2,$1); }
          | SMP CODE  {$$ = concat_node($2,$1); }
          | DECL CODE {$$ = concat_node($2,$1); }
          | {$$ = 0;}
          ;

SMP      : ASSIGN {$$ = $1;} 
         | CALL   {$$ = $1;}
         ;

CALL    : ID '(' PARAM_LIST ')' ';' {$$ = new_function_call_node($1, $3);}
        ;

PARAM_LIST : PARAM {$$ = $1;}
                | {$$ = 0;}
                ; 

PARAM : EXPRESSION { $$ = new_param_node($1);}
      | PARAM ',' PARAM {$$ = concat_lists($1,$3);}


DECL     : LET ID ':' T ';' {$$ = new_declaration_node($2, $4);}
         ;


LOOP    : WHILE '(' COND ')' '{' CODE '}' {$$ = new_loop_node($3,$6);}
          ;
CTL     : IF '(' COND ')' '{' CODE '}' {$$= new_if_node($3, $6);}
        ;


COND      : COND OR COND {$$ = new_compose_cond_node($1,$2,$3); }
          | COND AND COND {$$ = new_compose_cond_node($1,$2,$3); }
          | NOT COND {$$ = not_cond($2); }
          | EXPRESSION CONDITIONAL_OPERATOR EXPRESSION { $$ = $1 ;}
          | TRUE {$$ = new_true_node();}
          | FALSE {$$ = new_false_node();}
          ;

ASSIGN  : ID '=' EXPRESSION ';' {$$= new_assign_node($1, $3);}

   
EXPRESSION :            
           EXPRESSION OPERATOR EXPRESSION {$$ = new_compose_expr_node($1,$2,$3);}
          | ID  {$$ = new_var_node($1);}
          | VALUE {  $$ = $1; }
          | CALL {  $$ = $1 ;}
          ;   

VALUE :
          vTEXT {$$ = new_string_node($1);}
        | vINT {$$ = new_int_node($1);}
        | vDOUBLE {$$= new_double_node($1);}
        ;

OPERATOR  : '+'
          | '-'
          | '*'
          | '/'
          ;

CONDITIONAL_OPERATOR :  '<'
          | '>'
          | LE
          | GE
          | EQ
          | NE
          ;
        
T         : 
            INT 
          | DOUBLE
          | BOOL
          | RECTANGLE
          | CIRCLE
          | DOT
          | TEXT
          | LINE
          ;
%%

int yywrap(){
        return 1;
} 

int main() {
    printf("Enter the expression:\n");
    root_node_t * root = new_root_node();
    int ret= yyparse(root);
    
    //handle errors for ret values

    //call code generator
    generate_code(root);
} 