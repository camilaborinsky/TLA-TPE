%{

#include <stdio.h>
#include <stdlib.h>
#include "utils/symbol_table.h"

int yylex();
void yyerror();

%}

%union{
  char * string;
  int integer;
  float decimal;
  int type;
  variable * var;
  ast_node * node;
  root_node_t * rnode;
}

%token<string> ID
%token<type> INT DOUBLE BOOL RECTANGLE CIRCLE DOT TEXT LINE
%token TRUE FALSE VALUE IF WHILE FUNCTION LET LE GE EQ NE OR AND NOT BEGIN RETURN
%type<node> DECL ASSIGN CTL MAIN_CODE LOOP SMP FUNC PARAM_DECL_LIST PARAM_DECL CODE CALL PARAM_LIST PARAM COND EXPRESSION
%type<rnode> S
%parse-param {root_node_t * root}
%right "="
%left OR AND
%left '>' '<' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'
%start PROGRAM



%%

PROGRAM   : BEGIN  S  RETURN {return}
          | S {return}

S         : DECL S  {add_decl_node(root->global_variables,$1);}
          | FUNC S  {add_func_node(root->functions, $1);}
          | MAIN_CODE S {add_instructions(root->main, $1); }
          | 
          ;

MAIN_CODE : CTL MAIN_CODE {$$ = add_if_node($2,$1); }
          | LOOP MAIN_CODE {$$ = add_loop_node($2,$1); }
          | SMP MAIN_CODE {$$ = add_instruction_node($2, $1);}
          |
          ;

FUNC  : FUNCTION ID ':' T '(' PARAM_DECL_LIST ')' '{' CODE '}' {$$ = new_function_node($2, $4, $6, $9);}

PARAM_DECL_LIST : PARAM_DECL {$$ = $1}
                | {$$ = 0}
                ; 


PARAM_DECL : ID ':' T { $$ = new_param_decl_node($1,$3)}
           | PARAM_DECL ',' PARAM_DECL {$$ = concat_params_decl($1,$3)}
           ;

CODE      : CTL CODE {$$ = add_if_node($2,$1) }
          | LOOP CODE {$$ = add_loop_node($2,$1) }
          | SMP CODE  {$$ = add_instruction_node($2,$1) }
          | DECL CODE {$$ = add_decl_node($2,$1) }
          |
          ;

SMP      : ASSIGN {$$ = $1} 
         | CALL   {$$ = $1}
         ;

CALL    : ID '(' PARAM_LIST ')' ';' {$$ = new_function_call_node($1, $3);}
        ;

PARAM_LIST : PARAM {$$ = $1}
                | {$$ = 0}
                ; 

PARAM : ID { $$ = new_param_node($1,$3);}
      | PARAM ',' PARAM {$$ = concat_params($1,$3);}


DECL     : LET ID ':' T ';' {$$ = new_declaration_node($2, $5);}
         ;


LOOP    : WHILE '(' COND ')' '{' CODE '}' {$$ = new_loop_node($3,$6);}
          ;
CTL     : IF '(' COND ')' '{' CODE '}' {$$= new_if_node($3, $6);}
        ;


COND      : COND OR COND {$$ = new_compose_cond_node($1,$2,$3); }
          | COND AND COND {$$ = new_compose_cond_node($1,$2,$3); }
          | NOT COND {$$ = not_cond($3); }
          | EXPRESSION {$$ = $1 }
          | TRUE {$$ = new_true_node()}
          | FALSE {$$ = new_false_node()}
          ;

ASSIGN  : ID '=' EXPRESSION ';' {$$= new_assign_node($1, $3);}

   
EXPRESSION :            
          | EXPRESSION OPERATOR EXPRESSION {$$ = new_compose_expr_node($1,$2,$3)}
          | ID  {$$ = new_var_node($1)}
          | VALUE {  $$ = new_const_node($1) }
          | CALL {  $$ = $1 }
          ;   

OPERATOR  : '+'
          | '-'
          | '*'
          | '/'
          | '<'
          | '>'
          | LE
          | GE
          | EQ
          | NE


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
    int ret= yyparse(&root);
    
    //handle errors for ret values

    //call code generator
    
} 