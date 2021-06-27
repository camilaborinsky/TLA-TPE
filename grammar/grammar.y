%code requires {
        #include <stdio.h>
        #include <stdlib.h>
        #include "utils/types.h"
        #include "utils/symbol_table.h"
        #include "utils/code_generator.h"
        #include "utils/ast.h"
        extern int yylineno;
        int yylex();
        void yyerror(root_node_t * root, const char * msg);
}

%define parse.error verbose

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
%token<type> INT DOUBLE BOOL RECTANGLE CIRCLE DOT TEXT LINE FIGURE VOID
%token IF WHILE FUNCTION LET LE GE EQ NE NOT START RETURN END RIGHT_ARROW
%token<integer> OR AND JOIN
%token<value> vTEXT vINT vDOUBLE TRUE FALSE 
%type <integer> OPERATOR
%type<node> DECL ASSIGN DECL_ASSIGN CTL MAIN_CODE LOOP SMP FUNC PARAM_DECL_LIST PARAM_DECL CODE CALL PARAM_LIST PARAM EXPRESSION VALUE RET
%type<rnode> S
%type<type> T FUNC_T
%parse-param {root_node_t * root}
%right "="
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'
%start PROGRAM



%%

PROGRAM   : START  S  END { set_easter_egg(root); return 0;}
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

FUNC  : FUNCTION ID ':' FUNC_T '(' PARAM_DECL_LIST ')' {next_scope();} '{' CODE RET '}' {prev_scope();} {$$ = new_function_node($2, $4, $6, $10, $11);}

FUNC_T : T
       | VOID 

PARAM_DECL_LIST : PARAM_DECL {$$ = $1;}
                | {$$ = 0;}
                ; 


PARAM_DECL : ID ':' T { $$ = new_param_decl_node($1,$3);}
           | PARAM_DECL ',' PARAM_DECL {$$ = concat_lists($3,$1);}
           ;

CODE      : CTL CODE  {$$ = concat_node($2,$1); }
          | LOOP CODE {$$ = concat_node($2,$1); }
          | SMP CODE  {$$ = concat_node($2,$1); }
          | DECL CODE {$$ = concat_node($2,$1); }
          | DECL_ASSIGN';' CODE {$$ = concat_node($3,$1);} 
          | {$$ = 0;}
          ;

RET       : RETURN EXPRESSION ';' {$$ = new_return_node($2);}
          | RETURN ';' {$$ = new_return_node(0);}

SMP      : ASSIGN ';' {$$ = $1;} 
         | CALL  ';' { set_terminal($1); $$ = $1;}
         ;

CALL    : ID '(' PARAM_LIST ')' {$$ = new_function_call_node($1, $3);}
        | ID RIGHT_ARROW PARAM_LIST  {$$ = new_function_call_node($1, $3);}
        ;

PARAM_LIST : PARAM {$$ = $1;}
                |  {$$ = 0;}
                ; 

PARAM : EXPRESSION {$$ = new_param_node($1);}
      |  EXPRESSION',' PARAM  {$$ = concat_node($3,$1);}
      |'{' CODE RET '}' {$$ = new_lambda_function(root,$2,$3);}


DECL     : LET ID ':' T ';' {$$ = new_declaration_node($2, $4);}
         ;


LOOP    : WHILE '(' EXPRESSION ')' {next_scope();} '{' CODE '}' {prev_scope();} {$$ = new_loop_node($3,$7);}
          ;
CTL     : IF '(' EXPRESSION ')' {next_scope();} '{' CODE '}' {prev_scope();} {$$= new_if_node($3, $7);}
        ;


/* COND      : COND OR COND {$$ = new_compose_cond_node($1,$2,$3); }
          | COND AND COND {$$ = new_compose_cond_node($1,$2,$3); }
          | NOT COND {$$ = not_cond($2); }
          | EXPRESSION CONDITIONAL_OPERATOR EXPRESSION { $$ = $1 ;}
          | TRUE {$$ = new_true_node();}
          | FALSE {$$ = new_false_node();}
          ; */

ASSIGN  : ID '=' EXPRESSION {$$= new_assign_node($1, $3);}

DECL_ASSIGN : LET ID ':' T '=' EXPRESSION {$$ = new_assign_decl_node($2, $4, $6);} 
   
EXPRESSION :            
           EXPRESSION OPERATOR EXPRESSION {$$ = new_compose_expr_node($1,$2,$3);}
          | NOT EXPRESSION {$$ = not_expression_node($2);}
          | ID  {$$ = new_var_node($1);}
          | VALUE {  $$ = $1; }
          | CALL {$$ = $1;}
          | '(' EXPRESSION ')' {set_closed($2); $$=$2;}
          | ID JOIN ID {$$ = new_join_call($1,$3);}
          ;   

VALUE :
          vTEXT {$$ = new_string_node($1);}
        | vINT {$$ = new_int_node($1);}
        | vDOUBLE {$$ = new_double_node($1);}
        | TRUE {$$ = new_true_node();}
        | FALSE {$$ = new_false_node();}
        ;

OPERATOR  : '+' {$$ = ADD;}
          | '-' {$$ = SUB;}
          | '*' {$$ = MUL;}
          | '/' {$$ = DIV;}
          | '<' {$$ = LESS;}
          | '>' {$$ = GREATER;}
          | LE  {$$ = LESSEQ;}
          | GE  {$$ = GREATEQ;}
          | EQ  {$$ = EQUALS;}
          | NE  {$$ = NEQ;}
          | AND {$$ = oAND;}
          | OR {$$ = oOR;}
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
          | FIGURE
          ;
%%

int yywrap(){
        return 1;
} 

void yyerror(root_node_t * root, const char* msg){
        
        fprintf(stderr, "%s in line %d\n", msg, yylineno);
        exit(1);
}

int main() {
    root_node_t * root = new_root_node();
    int ret= yyparse(root);
    
    //handle errors for ret values

    //call code generator
    generate_code(root);
    exit(0);
} 